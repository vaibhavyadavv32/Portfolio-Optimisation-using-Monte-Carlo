import yfinance as yf
import pandas as pd

tickers = [
    "NVDA", "AVGO", "AMD", "ANET", "KLAC",
    "LRCX", "AMAT", "MU", "MPWR", "NOW",
    "MSFT", "META", "GOOGL", "AMZN", "NFLX",
    "ISRG", "LLY", "AXON", "COST", "V",
    "MA", "MELI", "ORLY", "CPRT", "FICO",
    "CTAS", "URI", "WST", "DECK", "TJX"
]
start_date = "2011-01-01"
end_date = "2026-08-31"

try:
    data = yf.download(tickers, start=start_date, end=end_date)["Close"]
    data.ffill(inplace=True)
    data.to_csv("stocks.csv")
    print("Downloaded and saved close prices to stocks.csv")
except Exception as e:
    print(f"Error downloading data: {e}")
