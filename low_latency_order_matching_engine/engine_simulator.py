import asyncio
import random
import time

# Exchange connection details
EXCHANGES = [
    ("127.0.0.1", 5001, "LSE"),
    ("127.0.0.1", 5002, "CHIX"),
    ("127.0.0.1", 5003, "TRQ"),
    ("127.0.0.1", 5004, "BATS"),
]

SYMBOLS = [f"SYM{i:02d}" for i in range(1, 11)]
SIDES = ["1", "2"]  # 1=Buy, 2=Sell

# Build FIX NewOrderSingle
def build_fix_order(order_id, symbol, side, qty, price):
    ts = time.strftime('%Y%m%d-%H:%M:%S')
    msg = [
        "35=D",        # NewOrderSingle
        f"11={order_id}",  # ClOrdID
        f"55={symbol}",    # Symbol
        f"54={side}",      # Side
        f"38={qty}",       # OrderQty
        f"44={price}",     # Price
        f"60={ts}",        # TransactTime
    ]
    return "|".join(msg) + "|"

async def order_engine():
    order_id = 1
    connections = []

    # Connect to all exchanges
    for host, port, name in EXCHANGES:
        reader, writer = await asyncio.open_connection(host, port)
        connections.append((reader, writer, name))
        print(f"[Order Engine] Connected to {name} at {host}:{port}")

    idx = 0
    try:
        while True:
            reader, writer, exch_name = connections[idx % len(connections)]

            # Random symbol, side, qty, price
            symbol = random.choice(SYMBOLS)
            side = random.choice(SIDES)
            qty = random.randint(1, 100)
            price = round(random.uniform(90, 110), 2)

            fix_order = build_fix_order(order_id, symbol, side, qty, price)
            order_id += 1

            print(f"\n[Order Engine -> {exch_name}] {fix_order}")
            writer.write(fix_order.encode())
            await writer.drain()

            # Wait for response
            try:
                data = await asyncio.wait_for(reader.read(1024), timeout=1.0)
                if data:
                    print(f"[{exch_name} -> Order Engine] {data.decode().strip()}")
            except asyncio.TimeoutError:
                print(f"[Order Engine] No response from {exch_name}")

            idx += 1
            await asyncio.sleep(1)  # 1 order/sec
    except KeyboardInterrupt:
        print("[Order Engine] Shutting down...")
    finally:
        for r, w, _ in connections:
            w.close()
            await w.wait_closed()

if __name__ == "__main__":
    asyncio.run(order_engine())
