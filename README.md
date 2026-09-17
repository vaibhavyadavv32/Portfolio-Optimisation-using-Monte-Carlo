# Portfolio Optimization using Monte Carlo Simulation

This project implements a portfolio optimization tool using Monte Carlo simulation to find the asset allocation that maximizes the Sharpe ratio. It includes C++ code for data processing and simulation, and a Python script for interactive visualization of the efficient frontier.

---

## Project Structure

```
/
├── DownloadHistoricalStocksData.py   # Downloads historical close prices via yfinance -> stocks.csv
├── DailyReturns.cpp                  # Computes daily log returns from stocks.csv -> stocks_with_DailyReturns.csv
├── Matrix.hpp                        # Matrix class: transpose, dot product, mean, covariance matrix
├── Portfolio.hpp                     # Portfolio class: caches mean returns + covariance, computes return/variance/risk/Sharpe
├── Utils.hpp                         # Utility functions: random weight generation, dot product, Sharpe ratio
├── main.cpp                          # Loads data, runs the Monte Carlo simulation, writes MonteCarloResults.csv
├── Visualisation.py                  # Plots the efficient frontier from MonteCarloResults.csv using Plotly
└── README.md
```

---

## How it works

1. **`DownloadHistoricalStocksData.py`** pulls daily close prices for a configurable list of tickers from Yahoo Finance and writes `stocks.csv`.
2. **`DailyReturns.cpp`** reads `stocks.csv` and computes the daily **log return** for each asset, `r_t = ln(P_t / P_{t-1})`, writing `stocks_with_DailyReturns.csv`.
3. **`main.cpp`**:
   - Parses `stocks_with_DailyReturns.csv`, dynamically detecting the number of assets from the CSV header.
   - Builds a `Matrix` of daily returns and constructs a `Portfolio` object, which caches the mean return vector and the N×N covariance matrix once.
   - Runs a configurable number of Monte Carlo trials. Each trial draws a random, non-negative weight vector (normalized to sum to 1), computes annualized return, annualized risk (using the √252 scaling rule), and the Sharpe ratio via the `Portfolio` class.
   - Tracks and reports the best-Sharpe portfolio found, and writes every valid trial's metrics and weights to `MonteCarloResults.csv`.
4. **`Visualisation.py`** reads `MonteCarloResults.csv` and renders an interactive Plotly scatter plot of risk vs. return, colored by Sharpe ratio, highlighting the optimal portfolio.

---

## Asset universe

The current ticker list in `DownloadHistoricalStocksData.py` spans semiconductors/AI infrastructure, mega-cap tech, healthcare, payments, and consumer/industrial compounders:

```
NVDA, AVGO, AMD, ANET, KLAC, LRCX, AMAT, MU, MPWR, NOW,
MSFT, META, GOOGL, AMZN, NFLX, ISRG, LLY, AXON, COST, V,
MA, MELI, ORLY, CPRT, FICO, CTAS, URI, WST, DECK, TJX
```

Date range: `2011-01-01` to `2026-08-31` (actual end date is capped by the latest available trading day). Tickers and date range are easily changed at the top of `DownloadHistoricalStocksData.py`.

---

## Prerequisites

- **C++ compiler** supporting C++11 or later (e.g. `g++`, `clang++`)
- **Python 3.6+** with:
  ```
  pip install pandas plotly yfinance
  ```

---

## Usage

**1. Download price data**
```
python DownloadHistoricalStocksData.py
```

**2. Compute daily log returns**
```
g++ -std=c++11 -O2 DailyReturns.cpp -o DailyReturns
./DailyReturns
```

**3. Run the Monte Carlo simulation**
```
g++ -std=c++11 -O2 main.cpp -o portfolio_sim
./portfolio_sim
```
Prints the best Sharpe ratio, annualized return, annualized risk, and optimal weights to the console, and writes `MonteCarloResults.csv`.

**4. Visualize the efficient frontier**
```
python Visualisation.py
```
Opens an interactive scatter plot in your browser and saves `Visualisation.html`.

---

## Notes

- Portfolio weights are drawn independently from a uniform distribution and normalized to sum to 1 — the model is long-only (no shorting, no leverage).
- Annualized return scales linearly with trading days (×252); annualized risk scales with the square root of trading days (×√252), per the standard time-scaling of variance.
- Sharpe ratio assumes a risk-free rate of 0 by default (configurable in `Utils.hpp`).
- Degenerate portfolios (near-zero risk or implausibly high Sharpe) are filtered out of the results.
- The random weight generator seeds its Mersenne Twister engine once per run and reuses it across all simulations, avoiding repeated entropy-source calls.

---

*Built by Vaibhav — Engineering Student, IIT Madras*
