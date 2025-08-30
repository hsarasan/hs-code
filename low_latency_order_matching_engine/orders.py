import asyncio
import random
import time

HOST = "127.0.0.1"
PORT = 9100
ORDERS_PER_SECOND = 5

SYMBOLS = [f"SYM{i:02d}" for i in range(1, 11)]
ORDER_COUNTER = 1

def random_fix_order():
    global ORDER_COUNTER
    sym = random.choice(SYMBOLS)
    side = random.choice(["1", "2"])  # 1=Buy, 2=Sell
    qty = random.randint(1, 100)
    price = round(random.uniform(10, 12), 2)
    ord_type = "2"  # Limit order
    ts = time.time_ns()
    cl_ord_id = str(ORDER_COUNTER)
    ORDER_COUNTER += 1

    # Build FIX 4.2 NewOrderSingle
    fields = [
        "8=FIX.4.2",
        "35=D",
        f"11={cl_ord_id}",
        f"55={sym}",
        f"54={side}",
        f"38={qty}",
        f"44={price}",
        f"40={ord_type}",
        "49=CLIENT",
        "56=EXCH",
        f"60={ts}",
        "10=000"
    ]
    return "|".join(fields) + "|"

async def send_orders():
    reader, writer = await asyncio.open_connection(HOST, PORT)
    print(f"[CLIENT] Connected to {HOST}:{PORT}")
    interval = 1.0 / ORDERS_PER_SECOND

    try:
        while True:
            order = random_fix_order()
            writer.write((order + "\n").encode())
            await writer.drain()
            print(f"[CLIENT -> 9100] {order.strip()}")
            await asyncio.sleep(interval)
    except KeyboardInterrupt:
        print("[CLIENT] Stopping...")
    finally:
        writer.close()
        await writer.wait_closed()

if __name__ == "__main__":
    asyncio.run(send_orders())
