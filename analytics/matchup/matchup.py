import streamlit as st
from components.stat_bar import render_stat_bar
from utils.images import get_player_image_url


def _stat_row(label: str, v1: float, v2: float, is_pct: bool = False) -> str:
    fmt = lambda v: f"{v:.1f}%" if is_pct else str(int(v))
    c1 = "stat-val-win" if v1 >= v2 else "stat-val-lose"
    c2 = "stat-val-win" if v2 >= v1 else "stat-val-lose"
    bar = render_stat_bar(v1, v2)
    return f"""
<div style="margin-bottom:18px;">
  <div class="stat-bar-label">{label}</div>
  <div class="stat-bar-row">
    <div class="stat-val-left {c1}">{fmt(v1)}</div>
    <div style="width:4px;"></div>
    <div class="stat-val-right {c2}">{fmt(v2)}</div>
  </div>
  {bar}
</div>
"""


def show_matchup(df):
    st.markdown(
        '<div class="section-header"><span class="section-dot"></span>⚔️ Head-to-Head Matchup</div>',
        unsafe_allow_html=True,
    )
    player_list = df["Name"].tolist()
    sel1, sel2 = st.columns(2)
    p1_name = sel1.selectbox("Player 1", player_list, index=0)
    p2_name = sel2.selectbox("Player 2", player_list, index=min(1, len(player_list)-1))

    p1 = df[df["Name"] == p1_name].iloc[0]
    p2 = df[df["Name"] == p2_name].iloc[0]
    img1 = get_player_image_url(p1_name)
    img2 = get_player_image_url(p2_name)

    st.markdown("<br>", unsafe_allow_html=True)
    hc1, hc_vs, hc2 = st.columns([3, 1, 3])

    with hc1:
        st.markdown(f"""
<div style="text-align:center;">
  <img src="{img1}" style="width:100px;height:100px;border-radius:50%;
    object-fit:cover;border:3px solid #3B82F6;background:#0F172A;"
    onerror="this.src='https://cdn-icons-png.flaticon.com/512/847/847969.png'" />
  <div class="matchup-player-name">{p1_name}</div>
</div>""", unsafe_allow_html=True)

    with hc_vs:
        st.markdown('<div class="vs-badge" style="padding-top:35px;">VS</div>',
                    unsafe_allow_html=True)

    with hc2:
        st.markdown(f"""
<div style="text-align:center;">
  <img src="{img2}" style="width:100px;height:100px;border-radius:50%;
    object-fit:cover;border:3px solid #F97316;background:#0F172A;"
    onerror="this.src='https://cdn-icons-png.flaticon.com/512/847/847969.png'" />
  <div class="matchup-player-name">{p2_name}</div>
</div>""", unsafe_allow_html=True)

    st.markdown("<br>", unsafe_allow_html=True)

    stats = [
        ("Points",     "Points",         False),
        ("Rebounds",   "Total_Reb",       False),
        ("Assists",    "Assists",         False),
        ("Steals",     "Steals",          False),
        ("Blocks",     "Blocks",          False),
        ("Turnovers",  "Turnovers",       False),
        ("2PT %",      "2pt %",           True),
        ("3PT %",      "3pt %",           True),
        ("Def. Plays", "Defensive_Plays", False),
    ]
    html = '<div class="matchup-container">'
    for label, col, is_pct in stats:
        html += _stat_row(label, float(p1[col]), float(p2[col]), is_pct)
    html += "</div>"
    st.markdown(html, unsafe_allow_html=True)
