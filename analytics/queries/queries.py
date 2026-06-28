import streamlit as st
from components.player_card import render_player_card


def show_queries(df):
    st.markdown(
        '<div class="section-header"><span class="section-dot"></span>🔎 Database Query Engine</div>',
        unsafe_allow_html=True,
    )

    fc1, fc2, fc3 = st.columns(3)
    with fc1:
        min_pts = st.slider("Min Points",   0, int(df["Points"].max()),    0)
    with fc2:
        min_reb = st.slider("Min Rebounds", 0, int(df["Total_Reb"].max()), 0)
    with fc3:
        min_ast = st.slider("Min Assists",  0, int(df["Assists"].max()),   0)

    filtered = df[
        (df["Points"]    >= min_pts) &
        (df["Total_Reb"] >= min_reb) &
        (df["Assists"]   >= min_ast)
    ]

    st.markdown(
        f'<div style="color:#64748B;font-size:0.85rem;margin:0.5rem 0 1rem;">'
        f'Found <strong style="color:#3B82F6;">{len(filtered)}</strong> players</div>',
        unsafe_allow_html=True,
    )

    display_cols = ["Name","Points","Total_Reb","Assists","Steals",
                    "Blocks","Turnovers","Fouls","2pt %","3pt %"]
    col_dl, _ = st.columns([1, 4])
    with col_dl:
        st.download_button("⬇ Download CSV",
            filtered[display_cols].to_csv(index=False),
            "filtered_players.csv", "text/csv", use_container_width=True)

    st.markdown("<br>", unsafe_allow_html=True)

    if filtered.empty:
        st.info("No players match the selected filters.")
        return

    cols_per_row = 4
    rows = [filtered.iloc[i:i+cols_per_row] for i in range(0, len(filtered), cols_per_row)]
    for row_slice in rows:
        cols = st.columns(cols_per_row)
        for col, (_, player) in zip(cols, row_slice.iterrows()):
            with col:
                st.markdown(render_player_card(player), unsafe_allow_html=True)
        st.markdown("<br>", unsafe_allow_html=True)
