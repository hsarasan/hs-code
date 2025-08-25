# fix_orderbook_publisher.py
import asyncio
import random
import math
import time
import datetime
import signal
import os
from dataclasses import dataclass
from typing import List, Dict, Set

# ----------------------------
# Configuration / CLI parsing
# ----------------------------
import argparse

def parse_args():
    p = argparse.ArgumentParser(description="Simulate FTSE-100-like order books in FIX over TCP.")
    p.add_argument("--host", default="127.0.0.1", help="Bind host (default: 127.0.0.1)")
    p.add_argument("--port", type=int, default=9000, help="Bind port (default: 9000)")
    p.add_argument("--levels", type=int, default=5, help="Price levels per side (default: 5)")
    p.add_argument("--hz", type=float, default=5.0, help="Updates per second per symbol per venue (default: 5)")
    p.add_argument("--seed", type=int, default=42, help="RNG seed (default: 42)")
    p.add_argument("--tick-size-bps", type=float, default=1.0, help="Tick size in basis points of price")
    p.add_argument("--base-spread-bps", type=float, default=5.0, help="Approx. half-spread in bps")
    p.add_argument("--notional", type=float, default=1_000_000.0, help="Average notional per level")
    return p.parse_args()

EXCHANGES = ["LSE", "CHIX", "BATS", "TRX"]

# ----------------------------
# Data structures
# ----------------------------
@dataclass
class Level:
    price: float
    size: int

@dataclass
class Book:
    symbol: str
    venue: str
    ts: float
    bids: List[Level]
    asks: List[Level]

    def to_fix(self, mdreqid: int) -> str:
        """
        Convert the Book snapshot to a FIX Market Data Snapshot/Full Refresh (35=W)
        """
        fix = [
            "8=FIX.4.4",
            "35=W",
            f"55={self.symbol}",
            f"48={hash(self.symbol)%1000}",  # simple SecurityID
            "22=8",  # ISIN-like dummy
            f"262={mdreqid}",  # MDReqID
            f"268={len(self.bids)+len(self.asks)}"
        ]
        for l in self.bids:
            fix += [ "269=0", f"270={l.price:.4f}", f"271={l.size}" ]  # Bid
        for l in self.asks:
            fix += [ "269=1", f"270={l.price:.4f}", f"271={l.size}" ]  # Ask
        ts_str = datetime.datetime.utcfromtimestamp(self.ts).strftime("%Y%m%d-%H:%M:%S.%f")[:-3]
        fix.append(f"60={ts_str}")
        return "|".join(fix) + "|"

# ----------------------------
# Price simulation
# ----------------------------
class PriceProcess:
    def __init__(self, start_price: float, kappa: float = 0.05, sigma: float = 0.10, ref: float = None):
        self.p = start_price
        self.kappa = kappa
        self.sigma = sigma
        self.ref = ref if ref is not None else start_price

    def step(self, dt: float) -> float:
        drift = self.kappa * (self.ref - self.p) * dt
        noise = self.sigma * math.sqrt(dt) * random.gauss(0.0,1.0)
        self.p = max(0.01, self.p * (1.0 + drift + noise))
        return self.p

# ----------------------------
# Order Book Factory
# ----------------------------
class OrderBookFactory:
    def __init__(self, levels: int, tick_bps: float, base_spread_bps: float, avg_notional: float):
        self.levels = levels
        self.tick_bps = tick_bps / 10_000.0
        self.base_spread_bps = base_spread_bps / 10_000.0
        self.avg_notional = avg_notional

    def _tick(self, price: float) -> float:
        return max(0.0001, price * self.tick_bps)

    def build_book(self, symbol: str, venue: str, mid: float) -> Book:
        ts = time.time()
        venue_bias_bps = {"LSE":0.9,"CHIX":1.0,"BATS":1.05,"TRX":1.1}[venue]
        half_spread = max(self._tick(mid), mid * self.base_spread_bps * venue_bias_bps)
        tick = self._tick(mid)

        best_bid = mid - half_spread
        best_ask = mid + half_spread

        bids, asks = [], []

        for i in range(self.levels):
            bid_px = round(best_bid - i*tick,6)
            ask_px = round(best_ask + i*tick,6)
            bid_size = int(max(1,(self.avg_notional/bid_px)*(1-0.07*i)*random.uniform(0.6,1.4)))
            ask_size = int(max(1,(self.avg_notional/ask_px)*(1-0.07*i)*random.uniform(0.6,1.4)))
            bids.append(Level(price=bid_px, size=bid_size))
            asks.append(Level(price=ask_px, size=ask_size))
        bids.sort(key=lambda l:l.price, reverse=True)
        asks.sort(key=lambda l:l.price)
        return Book(symbol=symbol, venue=venue, ts=ts, bids=bids, asks=asks)

# ----------------------------
# Market Simulator
# ----------------------------
class MarketSimulator:
    def __init__(self, symbols: List[str], venues: List[str], levels: int, tick_bps: float,
                 base_spread_bps: float, avg_notional: float, hz: float):
        self.symbols = symbols
        self.venues = venues
        self.hz = hz
        self.dt = 1.0 / hz
        self.proc: Dict[str, PriceProcess] = {}
        self.factory = OrderBookFactory(levels, tick_bps, base_spread_bps, avg_notional)
        for sym in symbols:
            start = random.uniform(50.0,500.0)
            ref = start*random.uniform(0.9,1.1)
            self.proc[sym] = PriceProcess(start_price=start, kappa=random.uniform(0.02,0.08),
                                          sigma=random.uniform(0.05,0.25), ref=ref)

    def step_books(self) -> List[Book]:
        books=[]
        for sym in self.symbols:
            mid = self.proc[sym].step(self.dt)
            for venue in self.venues:
                books.append(self.factory.build_book(sym, venue, mid*random.uniform(0.999,1.001)))
        return books

# ----------------------------
# TCP Publisher
# ----------------------------
class TCPPubServer:
    def __init__(self, host: str, port: int, simulator: MarketSimulator):
        self.host = host
        self.port = port
        self.sim = simulator
        self.clients: Set[asyncio.StreamWriter] = set()
        self._running = True

    async def start(self):
        server = await asyncio.start_server(self._handle_client, self.host, self.port)
        addr = ", ".join(str(sock.getsockname()) for sock in server.sockets)
        print(f"[FIX PUB] Listening on {addr}")
        async with server:
            broadcaster = asyncio.create_task(self._broadcast_loop())
            await server.serve_forever()
            broadcaster.cancel()

    async def _handle_client(self, reader: asyncio.StreamReader, writer: asyncio.StreamWriter):
        peer = writer.get_extra_info("peername")
        self.clients.add(writer)
        print(f"[FIX PUB] Client connected: {peer} (total {len(self.clients)})")
        try:
            while not reader.at_eof():
                await asyncio.sleep(1.0)
        except asyncio.CancelledError:
            pass
        finally:
            self.clients.discard(writer)
            try:
                writer.close()
                await writer.wait_closed()
            except Exception:
                pass
            print(f"[FIX PUB] Client disconnected: {peer} (total {len(self.clients)})")

    async def _broadcast_loop(self):
        interval = self.sim.dt
        mdreqid = 0
        while self._running:
            t0 = time.perf_counter()
            books = self.sim.step_books()
            payloads=[]
            for b in books:
                mdreqid+=1
                payloads.append(b.to_fix(mdreqid)+"\n")
            dead=[]
            for w in list(self.clients):
                try:
                    for pl in payloads:
                        w.write(pl.encode("utf-8"))
                    await w.drain()
                except Exception:
                    dead.append(w)
            for w in dead:
                self.clients.discard(w)
                try:
                    w.close()
                    await w.wait_closed()
                except Exception:
                    pass
            elapsed = time.perf_counter()-t0
            await asyncio.sleep(max(0.0, interval-elapsed))

    def stop(self):
        self._running=False

# ----------------------------
# Main
# ----------------------------
def make_symbols(n: int=100) -> List[str]:
    return [f"STK{i:03d}" for i in range(1,n+1)]

def main():
    args = parse_args()
    random.seed(args.seed)
    os.environ["PYTHONHASHSEED"] = str(args.seed)

    symbols = make_symbols(100)
    venues = EXCHANGES

    sim = MarketSimulator(
        symbols=symbols,
        venues=venues,
        levels=args.levels,
        tick_bps=args.tick_size_bps,
        base_spread_bps=args.base_spread_bps,
        avg_notional=args.notional,
        hz=args.hz
    )
    server = TCPPubServer(args.host, args.port, sim)

    loop = asyncio.get_event_loop()

    def _shutdown():s
        print("[FIX PUB] Shutting down...")
        server.stop()
        for task in asyncio.all_tasks(loop):
            task.cancel()

    for sig in (signal.SIGINT, signal.SIGTERM):
        try:
            loop.add_signal_handler(sig, _shutdown)
        except NotImplementedError:
            pass

    try:
        loop.run_until_complete(server.start())
    except asyncio.CancelledError:
        pass
    finally:
        pending = asyncio.all_tasks(loop)
        for t in pending:
            t.cancel()
        try:
            loop.run_until_complete(asyncio.gather(*pending, return_exceptions=True))
        except Exception:
            pass
        loop.close()

if __name__=="__main__":
    main()
