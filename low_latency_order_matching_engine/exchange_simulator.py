import asyncio
import random

# Exchange ports
EXCHANGES = {
    "LSE": 5001,
    "CHIX": 5002,
    "TRQ": 5003,
    "BATS": 5004,
}

def generate_fix_execution_report(order_msg, accepted=True):
    """Generate a simple FIX Execution Report (35=8)"""
    fields = order_msg.strip().split("|")
    order_id = next((f.split("=")[1] for f in fields if f.startswith("11=")), "UNKNOWN")

    response = [
        "8=FIX.4.2",
        f"37={order_id}",  # OrderID
        f"11={order_id}",  # ClOrdID
        "17=1",            # ExecID
        "20=0",            # ExecTransType
        "39=" + ("2" if accepted else "8"),  # OrdStatus: 2=Filled, 8=Rejected
        "150=" + ("F" if accepted else "8"), # ExecType: F=Filled, 8=Rejected
        "10=000"
    ]
    return "|".join(response) + "\n"

async def handle_client(reader, writer, exchange_name):
    addr = writer.get_extra_info('peername')
    print(f"[{exchange_name}] Connection from {addr}")

    try:
        while True:
            data = await reader.read(1024)
            if not data:
                break
            message = data.decode().strip()
            if not message:
                continue

            # Print request
            print(f"[{exchange_name}] Received: {message}")

            # Random 20% rejection
            accepted = random.random() > 0.2
            response = generate_fix_execution_report(message, accepted)

            # Print and send response
            print(f"[{exchange_name}] Sending response: {response.strip()}")
            writer.write(response.encode())
            await writer.drain()
    except ConnectionResetError:
        print(f"[{exchange_name}] Connection lost: {addr}")
    finally:
        writer.close()
        await writer.wait_closed()
        print(f"[{exchange_name}] Connection closed: {addr}")

async def start_exchange(name, port):
    server = await asyncio.start_server(
        lambda r, w: handle_client(r, w, name),
        "127.0.0.1",
        port
    )
    addrs = ", ".join(str(sock.getsockname()) for sock in server.sockets)
    print(f"[{name}] Listening on {addrs}")
    async with server:
        await server.serve_forever()

async def main():
    tasks = [start_exchange(name, port) for name, port in EXCHANGES.items()]
    await asyncio.gather(*tasks)

if __name__ == "__main__":
    asyncio.run(main())
