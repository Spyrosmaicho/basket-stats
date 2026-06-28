import os
import sqlite3
import numpy as np
import pandas as pd
import streamlit as st
from config import DB_PATH


@st.cache_data(ttl=30, show_spinner=False)
def load_data() -> pd.DataFrame:
    """Load player data from SQLite. Cached for 30 seconds."""
    if not os.path.exists(DB_PATH):
        return pd.DataFrame()

    conn = sqlite3.connect(DB_PATH)
    df = pd.read_sql_query("SELECT * FROM players", conn)
    conn.close()

    if df.empty:
        return pd.DataFrame()

    df.rename(columns={
        "FT_Pct":     "1pt %",
        "TwoP_Pct":   "2pt %",
        "ThreeP_Pct": "3pt %",
    }, inplace=True)

    df["Total_Reb"]       = df["Off_Reb"] + df["Def_Reb"]
    df["Defensive_Plays"] = df["Steals"] + df["Blocks"]
    df["TS_Pct"] = np.where(
        df["Points"] > 0,
        (df["Points"] / (2 * (df["Points"] * 0.88))) * 100,
        0,
    )
    return df.fillna(0)
