# exchange_simulator.py
import asyncio
import random
import time

# Exchange to port mapping
EXCHANGES = {
    "LSE": 9101,
    "CHIX": 9102,
    "TRQ": 9103,
    "BATS": 9104,
}

# ----------------------------
# FIX Helpers
# ----------------------------
def parse_fix(msg: str) -> dict:
    """Convert FIX string into dict (pipe separated for readability)."""
    return {kv.split("=")[0]: kv.split("=")[1] for kv in msg.strip().split("|") if kv}

def build_fix(fields: dict) -> str:
    """Convert dict into FIX string (pipe separated)."""
    return "|".join(f"{k}={v}" for k,v in fields.items()) + "|"

# ----------------------------
# Connection handler
# ----------------------------
async def handle_client(reader, writer, exchange):
    addr = writer.get_extra_info("peername")
    print(f"[{exchange}] Connection from {addr}")
    try:
        while True:
            data = await reader.readline()
            if not data:
                break
            msg = data.decode().strip()
            order = parse_fix(msg)
            cl_ord_id = order.get("11", "UNKNOWN")
            client = order.get("49", "CLIENT?")
            now = time.time_ns()

            # Randomly reject 20% of orders
            reject = random.random() < 0.2
            exec_id = f"{exchange}{random.randint(1000,9999)}"

            response = {
                "35": "8",         # Execution Report
                "11": cl_ord_id,   # Client Order ID
                "17": exec_id,     # Execution ID
                "39": "8" if reject else "0",   # Order Status (8=Rejected, 0=New)
                "150": "8" if reject else "0",  # Exec Type (8=Rejected, 0=New)
                "49": exchange,    # SenderCompID = Exchange
                "56": client,      # TargetCompID = Client
                "60": now          # Timestamp
            }

            fix_resp = build_fix(response)
            writer.write((fix_resp + "\n").encode())
            await writer.drain()
            print(f"[{exchange}] Order {cl_ord_id} -> {'REJECTED' if reject else 'ACCEPTED'}")
    except Exception as e:
        print(f"[{exchange}] Error: {e}")
    finally:
        writer.close()
        await writer.wait_closed()
        print(f"[{exchange}] Connection closed {addr}")

# ----------------------------
# Main server loop
# ----------------------------
async def main():
    servers = []
    for exch, port in EXCHANGES.items():
        server = await asyncio.start_server(
            lambda r,w,exch=exch: handle_client(r,w,exch), "127.0.0.1", port
        )
        servers.append(server)
        print(f"[{exch}] Listening on 127.0.0.1:{port}")

    # Run all servers concurrently
    await asyncio.gather(*(s.serve_forever() for s in servers))

if __name__ == "__main__":
    asyncio.run(main())
