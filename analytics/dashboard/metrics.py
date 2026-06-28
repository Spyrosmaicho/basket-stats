import streamlit as st
from components.kpi_card import render_kpi_card


def show_metrics(df):
    st.markdown(
        '<div class="section-header"><span class="section-dot"></span>Season Highlights</div>',
        unsafe_allow_html=True,
    )

    top_scorer    = df.loc[df["Points"].idxmax()]
    top_playmaker = df.loc[df["Assists"].idxmax()]
    top_defender  = df.loc[df["Defensive_Plays"].idxmax()]
    top_rebounder = df.loc[df["Total_Reb"].idxmax()]

    c1, c2, c3, c4 = st.columns(4)
    cards = [
        (c1, " Top Scorer",       top_scorer["Name"],    f"{int(top_scorer['Points'])}",             "Total Points",  "gold"),
        (c2, " Best Playmaker",   top_playmaker["Name"], f"{int(top_playmaker['Assists'])}",          "Total Assists", "blue"),
        (c3, " Defensive Anchor", top_defender["Name"],  f"{int(top_defender['Defensive_Plays'])}",  "Stl + Blk",    "green"),
        (c4, " Top Rebounder",    top_rebounder["Name"], f"{int(top_rebounder['Total_Reb'])}",        "Total Reb",    "purple"),
    ]
    for col, label, name, value, unit, accent in cards:
        with col:
            st.markdown(render_kpi_card(label, name, value, unit, accent), unsafe_allow_html=True)

    st.markdown("<br>", unsafe_allow_html=True)
