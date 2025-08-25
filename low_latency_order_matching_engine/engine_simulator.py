# round_robin_client.py
import asyncio
import random
import time

EXCHANGES = {
    "LSE": 9101,
    "CHIX": 9102,
    "TRQ": 9103,
    "BATS": 9104,
}

symbols = [f"STK{i:03d}" for i in range(1, 21)]
clients = ["CLIENT1"]

# ----------------------------
# FIX Helpers
# ----------------------------
def build_fix(fields: dict) -> str:
    return "|".join(f"{k}={v}" for k,v in fields.items()) + "|"

def parse_fix(msg: str) -> dict:
    return {kv.split("=")[0]: kv.split("=")[1] for kv in msg.strip().split("|") if kv}

# ----------------------------
# Random Order Generator (FIX NewOrderSingle)
# ----------------------------
order_id = 1
def random_order(client_id, exchange):
    global order_id
    cl_ord_id = str(order_id)
    order_id += 1

    sym = random.choice(symbols)
    side = random.choice(["1", "2"])  # 1=Buy, 2=Sell
    qty = random.randint(1, 1000)
    price = round(random.uniform(50, 150), 2)
    ord_type = "2" if random.random() < 0.7 else "1"  # 2=Limit,1=Market
    ts = time.time_ns()

    return build_fix({
        "35": "D",          # NewOrderSingle
        "11": cl_ord_id,    # ClOrdID
        "55": sym,          # Symbol
        "54": side,         # Side
        "38": qty,          # OrderQty
        "44": price,        # Price
        "40": ord_type,     # OrdType
        "49": client_id,    # SenderCompID
        "56": exchange,     # TargetCompID
        "60": ts            # Timestamp
    })

# ----------------------------
# Client logic
# ----------------------------
async def connect_to_exchange(exchange, port):
    reader, writer = await asyncio.open_connection("127.0.0.1", port)
    return reader, writer

async def round_robin_client():
    # Connect to all exchanges
    connections = {}
    for exch, port in EXCHANGES.items():
        reader, writer = await connect_to_exchange(exch, port)
        connections[exch] = (reader, writer)
        print(f"[CLIENT] Connected to {exch} on port {port}")

    exchanges = list(EXCHANGES.keys())
    i = 0

    try:
        while True:
            exch = exchanges[i % len(exchanges)]
            reader, writer = connections[exch]

            # Generate FIX order
            order = random_order("CLIENT1", exch)
            writer.write((order + "\n").encode())
            await writer.drain()
            print(f"[CLIENT -> {exch}] {order}")

            # Wait for response
            resp = await reader.readline()
            if resp:
                fix_resp = parse_fix(resp.decode().strip())
                print(f"[{exch} -> CLIENT] {fix_resp}")

            await asyncio.sleep(1)  # 1 message/sec
            i += 1
    except KeyboardInterrupt:
        print("[CLIENT] Stopping...")
    finally:
        for r, w in connections.values():
            w.close()
            await w.wait_closed()

# ----------------------------
# Main
# ----------------------------
if __name__ == "__main__":
    asyncio.run(round_robin_client())
