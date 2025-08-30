import asyncio
import random
import json
import time

# Exchanges and ports
EXCHANGES = {
    "LSE": 9001,
    "CHIX": 9002,
    "TRQ": 9003,
    "BATS": 9004
}

# Symbols to publish
SYMBOLS = [f"SYM{i}" for i in range(1, 11)]  # SYM1 ... SYM10

# Generate a random order book snapshot for a symbol
def generate_order_book(symbol, exchange):
    bids = [{"price": round(100 + random.random(), 2), "qty": random.randint(1, 100)} for _ in range(5)]
    asks = [{"price": round(101 + random.random(), 2), "qty": random.randint(1, 100)} for _ in range(5)]
    return {
        "exchange": exchange,
        "symbol": symbol,
        "timestamp": time.time(),
        "bids": bids,
        "asks": asks
    }

async def handle_client(reader, writer, exchange):
    addr = writer.get_extra_info('peername')
    print(f"Client connected from {addr} to {exchange}")

    try:
        while True:
            # Generate snapshots for all symbols
            for symbol in SYMBOLS:
                snapshot = generate_order_book(symbol, exchange)
                message = json.dumps(snapshot) + "\n"
                writer.write(message.encode())
            await writer.drain()

            await asyncio.sleep(1)  # publish every second
    except asyncio.CancelledError:
        print(f"Client {addr} disconnected from {exchange}")
    except Exception as e:
        print(f"Error with client {addr} on {exchange}: {e}")
    finally:
        writer.close()
        await writer.wait_closed()

async def start_exchange(exchange, port):
    server = await asyncio.start_server(
        lambda r, w: handle_client(r, w, exchange),
        host="0.0.0.0",
        port=port
    )
    print(f"{exchange} publishing on port {port}")
    async with server:
        await server.serve_forever()

async def main():
    tasks = [start_exchange(exchange, port) for exchange, port in EXCHANGES.items()]
    await asyncio.gather(*tasks)

if __name__ == "__main__":
    asyncio.run(main())
