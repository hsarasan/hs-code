# client_order_generator_100.py
import asyncio
import random
import time
import json

NUM_SYMBOLS = 100
NUM_CLIENTS = 100
ORDERS_PER_SECOND = 5  # total orders per second
HOST = "127.0.0.1"
PORT = 9100
SEED = 42

# ----------------------------
# Symbols and Clients
# ----------------------------
symbols = [f"STK{i:03d}" for i in range(1, NUM_SYMBOLS+1)]
clients = [f"CLT{i:03d}" for i in range(1, NUM_CLIENTS+1)]
random.seed(SEED)

# assign a reference mid-price per symbol
mid_prices = {s: random.uniform(50,500) for s in symbols}

# ----------------------------
# Random Order Generator
# ----------------------------
def random_order():
    sym = random.choice(symbols)
    client = random.choice(clients)
    side = random.choice(["BUY","SELL"])
    qty = random.randint(1, 1000)
    price = round(mid_prices[sym] * (1 + random.uniform(-0.01, 0.01)), 2)
    ord_type = "LIMIT" if random.random() < 0.7 else "MARKET"
    ts = time.time_ns()
    return {
        "client": client,
        "symbol": sym,
        "side": side,
        "type": ord_type,
        "qty": qty,
        "price": price,
        "ts": ts
    }

# ----------------------------
# TCP Publisher
# ----------------------------
async def publish_orders():
    reader, writer = await asyncio.open_connection(HOST, PORT)
    print(f"[CLIENT] Connected to {HOST}:{PORT}")
    interval = 1.0 / ORDERS_PER_SECOND
    try:
        while True:
            order = random_order()
            writer.write((json.dumps(order)+"\n").encode())
            await writer.drain()
            await asyncio.sleep(interval)
    except KeyboardInterrupt:
        print("[CLIENT] Stopping...")
    finally:
        writer.close()
        await writer.wait_closed()

# ----------------------------
# Main
# ----------------------------
if __name__=="__main__":
    asyncio.run(publish_orders())
