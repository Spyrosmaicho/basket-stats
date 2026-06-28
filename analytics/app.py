import streamlit as st

st.set_page_config(
    page_title="Pro Hoops Analytics",
    page_icon="",
    layout="wide",
    initial_sidebar_state="expanded",
)

# ── Imports ────────────────────────────────────────────────────────────────
from styles              import load_css
from engine.database     import load_data
from sidebar.sidebar     import show_sidebar
from dashboard.hero      import show_hero
from dashboard.metrics   import show_metrics
from dashboard.leaderboard import show_leaderboard
from charts.charts       import show_charts
from queries.queries import show_queries
from matchup.matchup     import show_matchup
from ml.similarity       import show_similarity
from ml.clustering       import show_clustering

# ── Global CSS ─────────────────────────────────────────────────────────────
load_css()

# ── Data ───────────────────────────────────────────────────────────────────
df = load_data()

# ── Sidebar ────────────────────────────────────────────────────────────────
show_sidebar(df)

# ── Empty-state guard ──────────────────────────────────────────────────────
if df.empty:
    show_hero()
    st.markdown("<br>", unsafe_allow_html=True)
    st.markdown(
        """
<div style="text-align:center;padding:4rem 2rem;">
  <div style="font-size:4rem;margin-bottom:1rem;"></div>
  <div style="font-family:Poppins,sans-serif;font-size:1.6rem;font-weight:700;
    color:#F1F5F9;margin-bottom:0.6rem;">No Players Loaded</div>
  <div style="color:#64748B;font-size:0.95rem;">
    Use the Engine Control Panel in the sidebar to import data.
  </div>
</div>
""",
        unsafe_allow_html=True,
    )
    st.stop()

# ── Hero ───────────────────────────────────────────────────────────────────
show_hero()

# ── KPI Metrics ────────────────────────────────────────────────────────────
show_metrics(df)

# ── Tabs ───────────────────────────────────────────────────────────────────
tab1, tab2, tab3, tab4, tab5 = st.tabs([
    "  Analytics",
    "  Queries",
    "  Matchup",
    "  AI Scouting",
    "  Leaderboard",
])

with tab1:
    show_charts(df)

with tab2:
    show_queries(df)

with tab3:
    show_matchup(df)

with tab4:
    st.markdown(
        '<div class="section-header"><span class="section-dot"></span> AI Scouting & Clustering</div>',
        unsafe_allow_html=True,
    )
    show_similarity(df)
    st.markdown("---")
    show_clustering(df)

with tab5:
    show_leaderboard(df)
