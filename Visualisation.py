import pandas as pd
import plotly.express as px
import plotly.graph_objects as go

df = pd.read_csv("MonteCarloResults.csv")

max_idx = df['Sharpe'].idxmax()
best_row = df.loc[max_idx]

fig = px.scatter(
    df, x="Risk", y="Return", color="Sharpe",
    color_continuous_scale="Viridis", opacity=0.6,
    title="Efficient Frontier - Monte Carlo Simulation",
    labels={"Risk": "Annualized Risk (Std Dev)", "Return": "Annualized Return"},
    hover_data={"Sharpe": True, "Risk": True, "Return": True}
)

fig.add_trace(go.Scatter(
    x=[best_row["Risk"]],
    y=[best_row["Return"]],
    mode="markers+text",
    marker=dict(color="red", size=10, line=dict(color="black", width=1)),
    name="Max Sharpe Portfolio",
    text=[f"Sharpe: {best_row['Sharpe']:.2f}"],
    textposition="top center"
))

fig.update_layout(
    title_font_size=20,
    legend=dict(x=0.75, y=0.02),
    coloraxis_colorbar=dict(title="Sharpe Ratio"),
    template="plotly_white"
)

# Show plot
fig.show()
fig.write_html("Visualisation.html")