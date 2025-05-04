import socket
import time
import random

TICKERS = ["AAPL", "MSFT", "GOOG", "NVD", "WAL", "ORACLE"]
PRICES = {ticker: [8.00, 8.04] for ticker in TICKERS}  # BID, ASK

def update_price(bid, ask):
    delta = 0.01 if random.choice([True, False]) else -0.01
    bid = round(bid + delta, 2)
    ask = round(bid + 0.04, 2)
    return bid, ask

def generate_tick(ticker, bid, ask):
    return f"{ticker},BID,{bid:.2f},ASK,{ask:.2f},END"

def run_server():
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.bind(('0.0.0.0', 9000))
        s.listen(1)
        print("Tick server listening on port 9000...")
        conn, addr = s.accept()
        with conn:
            print(f"Connection established from {addr}")
            while True:
                for ticker in TICKERS:
                    bid, ask = PRICES[ticker]
                    bid, ask = update_price(bid, ask)
                    PRICES[ticker] = [bid, ask]
                    message = generate_tick(ticker, bid, ask) + '\n'
                    conn.sendall(message.encode())
                    time.sleep(0.05)

if __name__ == "__main__":
    run_server()

