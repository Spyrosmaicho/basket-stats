import streamlit as st
from components.leaderboard_card import render_leaderboard_card


def show_leaderboard(df):
    st.markdown(
        '<div class="section-header"><span class="section-dot"></span> Leaderboards</div>',
        unsafe_allow_html=True,
    )
    col1, col2, col3 = st.columns(3)
    categories = [
        (col1, " Top Scorers",      "Points",          "PTS"),
        (col2, " Top Playmakers",   "Assists",          "AST"),
        (col3, " Defensive Leaders","Defensive_Plays",  "STL+BLK"),
    ]
    for col, title, sort_col, label in categories:
        with col:
            st.markdown(
                f'<div style="font-family:Poppins,sans-serif;font-weight:700;'
                f'font-size:1rem;color:#F1F5F9;margin-bottom:12px;">{title}</div>',
                unsafe_allow_html=True,
            )
            top5 = df.sort_values(sort_col, ascending=False).head(5)
            html = "".join(
                render_leaderboard_card(i, row["Name"], row[sort_col], label)
                for i, (_, row) in enumerate(top5.iterrows())
            )
            st.markdown(html, unsafe_allow_html=True)
