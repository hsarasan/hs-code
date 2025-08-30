import asyncio
import random
import time

EXCHANGES = {
    "LSE": 9001,
    "CHIX": 9002,
    "TRQ": 9003,
    "BATS": 9004,
}

SYMBOLS = [f"SYM{i}" for i in range(10)]
NUM_CLIENTS = 3


# -------------------------
# Exchange Server
# -------------------------
async def handle_client(reader, writer, exchange_name):
    """Keeps connection open but we only push data from broadcaster"""
    addr = writer.get_extra_info('peername')
    print(f"{exchange_name}: Client connected {addr}")
    try:
        while True:
            await asyncio.sleep(3600)  # keep alive
    except asyncio.CancelledError:
        print(f"{exchange_name}: Closing connection {addr}")
        writer.close()
        await writer.wait_closed()


async def start_exchange(exchange_name, port, queues):
    server = await asyncio.start_server(
        lambda r, w: handle_client(r, w, exchange_name), "127.0.0.1", port
    )
    print(f"{exchange_name} started on port {port}")

    async def broadcaster():
        while True:
            # Generate order book snapshot for all symbols
            timestamp = time.time()
            for sym in SYMBOLS:
                bid = round(random.uniform(90, 110), 2)
                ask = bid + round(random.uniform(0.1, 1.0), 2)
                msg = f"{exchange_name}|{sym}|bid={bid}|ask={ask}|ts={timestamp}\n"
                for q in queues[exchange_name]:
                    await q.put(msg)
            await asyncio.sleep(1)

    asyncio.create_task(broadcaster())
    async with server:
        await server.serve_forever()


# -------------------------
# Clients
# -------------------------
async def client_task(client_id, exchange_name, port, queue):
    reader, writer = await asyncio.open_connection("127.0.0.1", port)
    print(f"Client {client_id} connected to {exchange_name} on port {port}")

    async def printer():
        while True:
            msg = await queue.get()
            print(f"[Client {client_id}] {msg.strip()}")

    asyncio.create_task(printer())
    await asyncio.sleep(3600)


async def main():
    queues = {ex: [asyncio.Queue() for _ in range(NUM_CLIENTS)] for ex in EXCHANGES}

    # Start exchanges
    for ex, port in EXCHANGES.items():
        asyncio.create_task(start_exchange(ex, port, queues))

    # Start clients
    for cid in range(NUM_CLIENTS):
        for ex, port in EXCHANGES.items():
            asyncio.create_task(client_task(cid, ex, port, queues[ex][cid]))

    await asyncio.sleep(3600)


if __name__ == "__main__":
    asyncio.run(main())
