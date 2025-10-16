import pandas as pd
import numpy as np
from datetime import datetime, timedelta
import random

def generate_tick_data(
    start_date="2024-01-01",
    end_date="2024-12-31",
    num_stocks=100,
    sectors=5,
    ticks_per_day=1000,
    seed=42
):
    random.seed(seed)
    np.random.seed(seed)

    # Stock symbols and sector/liquidity mappings
    stock_symbols = [f"ST{i+1}" for i in range(num_stocks)]
    sector_map = {s: random.randint(0, sectors - 1) for s in stock_symbols}
    liquidity_map = {s: random.uniform(0.2, 1.0) for s in stock_symbols}  # 0.2 = low, 1 = high liquidity

    # Trading hours (9:30–16:00)
    market_open = 9 * 60 + 30
    market_close = 16 * 60
    trading_minutes = market_close - market_open

    start_dt = datetime.strptime(start_date, "%Y-%m-%d")
    end_dt = datetime.strptime(end_date, "%Y-%m-%d")

    all_ticks = []
    current_dt = start_dt

    while current_dt <= end_dt:
        # Skip weekends
        if current_dt.weekday() >= 5:
            current_dt += timedelta(days=1)
            continue

        # Sector-level market factors for correlation
        sector_factors = {s: np.random.normal(0, 0.002, ticks_per_day) for s in range(sectors)}

        # Intraday volatility (U-shaped curve)
        t = np.linspace(0, np.pi, ticks_per_day)
        intraday_vol = 0.5 + 0.5 * np.sin(t)

        for stock in stock_symbols:
            base_price = random.uniform(20, 200)
            sector_id = sector_map[stock]
            liquidity = liquidity_map[stock]

            # Generate returns with sector correlation + idiosyncratic noise
            noise = np.random.normal(0, 0.001, ticks_per_day)
            returns = sector_factors[sector_id] + noise
            returns *= intraday_vol * (1.5 - liquidity)  # illiquid = more volatile

            prices = base_price * np.exp(np.cumsum(returns))

            # Bid/ask spread inversely proportional to liquidity
            spread_base = 0.001 + (1.0 - liquidity) * 0.005
            spread = spread_base * (1.2 - 0.4 * intraday_vol)
            bid_prices = prices * (1 - spread / 2)
            ask_prices = prices * (1 + spread / 2)

            # Trade frequency depends on liquidity
            trade_fraction = 0.1 + 0.5 * liquidity
            is_trade = np.random.rand(ticks_per_day) < trade_fraction
            event_type = np.where(is_trade, "TRADE", "QUOTE")

            last_prices = np.where(is_trade, prices, np.nan)
            volumes = np.where(is_trade, np.random.randint(10, 2000, ticks_per_day), 0)

            # Generate timestamps
            start_time = current_dt + timedelta(minutes=market_open)
            times = [start_time + timedelta(seconds=i * trading_minutes * 60 / ticks_per_day)
                     for i in range(ticks_per_day)]

            df = pd.DataFrame({
                "timestamp": times,
                "symbol": stock,
                "bid": bid_prices,
                "ask": ask_prices,
                "last": last_prices,
                "volume": volumes,
                "sector": sector_id,
                "liquidity": liquidity,
                "event_type": event_type
            })
            all_ticks.append(df)

        current_dt += timedelta(days=1)

    # Concatenate all ticks and forward-fill last price safely
    tick_data = pd.concat(all_ticks, ignore_index=True)
    tick_data["last"] = tick_data["last"].ffill()  # Future-proof

    return tick_data


if __name__ == "__main__":
    print("Generating realistic tick data with liquidity and event types...")
    tick_df = generate_tick_data(ticks_per_day=500, num_stocks=100, sectors=5)

    tick_df.to_csv("tick_data_clean.csv", index=False)
    print(f"✅ Generated {len(tick_df):,} ticks saved to 'tick_data_clean.csv'")

