import streamlit as st


def load_css():
    st.markdown("""
<style>
@import url('https://fonts.googleapis.com/css2?family=Inter:wght@300;400;500;600;700;800;900&family=Poppins:wght@400;500;600;700;800;900&display=swap');

/* ── GLOBAL RESET ─────────────────────────── */
*, *::before, *::after { box-sizing: border-box; margin: 0; padding: 0; }

html, body, [data-testid="stAppViewContainer"], [data-testid="stMain"] {
    background-color: #0F172A !important;
    color: #F8FAFC !important;
    font-family: 'Inter', sans-serif !important;
}

#MainMenu, footer, header { visibility: hidden; }

.block-container {
    padding-top: 0 !important;
    padding-bottom: 3rem !important;
    max-width: 1400px !important;
}

[data-testid="stSidebar"] {
    background: #0B1120 !important;
    border-right: 1px solid #1E293B !important;
}

/* ── HERO BANNER ──────────────────────────── */
.hero-section {
    background: linear-gradient(135deg, #0F172A 0%, #1E293B 40%, #0F172A 100%);
    border-bottom: 1px solid #1E3A5F;
    padding: 3.5rem 3rem 3rem;
    text-align: center;
    position: relative;
    overflow: hidden;
}
.hero-section::before {
    content: '';
    position: absolute;
    top: -60%;
    left: 50%;
    transform: translateX(-50%);
    width: 700px;
    height: 700px;
    background: radial-gradient(circle, rgba(59,130,246,0.12) 0%, transparent 70%);
    pointer-events: none;
}
.hero-badge {
    display: inline-flex;
    align-items: center;
    gap: 6px;
    background: rgba(59,130,246,0.15);
    border: 1px solid rgba(59,130,246,0.4);
    color: #60A5FA;
    font-size: 0.72rem;
    font-weight: 600;
    letter-spacing: 0.12em;
    text-transform: uppercase;
    padding: 5px 14px;
    border-radius: 999px;
    margin-bottom: 1.2rem;
}
.hero-title {
    font-family: 'Poppins', sans-serif;
    font-size: clamp(2.2rem, 5vw, 3.8rem);
    font-weight: 900;
    line-height: 1.1;
    letter-spacing: -0.02em;
    background: linear-gradient(135deg, #FFFFFF 0%, #93C5FD 60%, #3B82F6 100%);
    -webkit-background-clip: text;
    -webkit-text-fill-color: transparent;
    background-clip: text;
    margin-bottom: 0.8rem;
}
.hero-subtitle {
    color: #94A3B8;
    font-size: 1.05rem;
    font-weight: 400;
    margin-bottom: 2rem;
    letter-spacing: 0.01em;
}
.hero-pills {
    display: flex;
    justify-content: center;
    flex-wrap: wrap;
    gap: 10px;
    margin-bottom: 2.2rem;
}
.hero-pill {
    background: rgba(30,41,59,0.8);
    border: 1px solid #334155;
    color: #CBD5E1;
    font-size: 0.78rem;
    font-weight: 500;
    padding: 5px 14px;
    border-radius: 999px;
}
.hero-pill span { margin-right: 5px; }

/* ── CARDS ────────────────────────────────── */
.glass-card {
    background: #1E293B;
    border: 1px solid #334155;
    border-radius: 16px;
    padding: 20px;
    transition: transform 0.25s ease, box-shadow 0.25s ease, border-color 0.25s ease;
    box-shadow: 0 4px 24px rgba(0,0,0,0.3);
}
.glass-card:hover {
    transform: translateY(-4px);
    box-shadow: 0 12px 40px rgba(0,0,0,0.45);
    border-color: #3B82F6;
}

/* ── KPI METRIC CARDS ─────────────────────── */
.kpi-card {
    background: linear-gradient(135deg, #1E293B 0%, #162032 100%);
    border: 1px solid #334155;
    border-radius: 20px;
    padding: 24px 20px;
    text-align: center;
    transition: all 0.3s ease;
    box-shadow: 0 6px 24px rgba(0,0,0,0.3);
    position: relative;
    overflow: hidden;
}
.kpi-card::after {
    content: '';
    position: absolute;
    top: 0; left: 0; right: 0;
    height: 3px;
    border-radius: 20px 20px 0 0;
}
.kpi-card.gold::after   { background: linear-gradient(90deg, #F59E0B, #FBBF24); }
.kpi-card.blue::after   { background: linear-gradient(90deg, #3B82F6, #60A5FA); }
.kpi-card.green::after  { background: linear-gradient(90deg, #22C55E, #4ADE80); }
.kpi-card.purple::after { background: linear-gradient(90deg, #A855F7, #C084FC); }
.kpi-card:hover {
    transform: translateY(-5px);
    box-shadow: 0 16px 48px rgba(0,0,0,0.5);
    border-color: #3B82F6;
}
.kpi-label {
    font-size: 0.72rem;
    font-weight: 600;
    letter-spacing: 0.12em;
    text-transform: uppercase;
    color: #64748B;
    margin-bottom: 10px;
}
.kpi-avatar {
    width: 64px;
    height: 64px;
    border-radius: 50%;
    object-fit: cover;
    border: 2px solid #334155;
    margin: 0 auto 10px;
    display: block;
    background: #0F172A;
}
.kpi-name {
    font-family: 'Poppins', sans-serif;
    font-size: 1.05rem;
    font-weight: 700;
    color: #F1F5F9;
    margin-bottom: 4px;
    white-space: nowrap;
    overflow: hidden;
    text-overflow: ellipsis;
}
.kpi-value {
    font-size: 1.6rem;
    font-weight: 800;
    color: #3B82F6;
    line-height: 1;
}
.kpi-unit {
    font-size: 0.75rem;
    color: #64748B;
    font-weight: 500;
    margin-top: 3px;
}

/* ── SECTION HEADERS ─────────────────────── */
.section-header {
    font-family: 'Poppins', sans-serif;
    font-size: 1.4rem;
    font-weight: 700;
    color: #F1F5F9;
    padding: 1.8rem 0 0.8rem;
    display: flex;
    align-items: center;
    gap: 10px;
    border-bottom: 1px solid #1E293B;
    margin-bottom: 1.2rem;
}
.section-dot {
    width: 8px; height: 8px;
    border-radius: 50%;
    background: #3B82F6;
    display: inline-block;
}

/* ── LEADERBOARD CARDS ───────────────────── */
.lb-card {
    display: flex;
    align-items: center;
    gap: 14px;
    background: #1E293B;
    border: 1px solid #334155;
    border-radius: 14px;
    padding: 14px 18px;
    margin-bottom: 10px;
    transition: all 0.25s ease;
}
.lb-card:hover {
    background: #243247;
    border-color: #3B82F6;
    transform: translateX(4px);
}
.lb-rank {
    font-family: 'Poppins', sans-serif;
    font-size: 1.1rem;
    font-weight: 800;
    width: 28px;
    text-align: center;
    flex-shrink: 0;
}
.lb-rank.gold   { color: #F59E0B; }
.lb-rank.silver { color: #94A3B8; }
.lb-rank.bronze { color: #B45309; }
.lb-rank.other  { color: #475569; }
.lb-avatar {
    width: 44px;
    height: 44px;
    border-radius: 50%;
    object-fit: cover;
    border: 2px solid #334155;
    flex-shrink: 0;
    background: #0F172A;
}
.lb-info { flex: 1; min-width: 0; }
.lb-name {
    font-weight: 600;
    font-size: 0.92rem;
    color: #F1F5F9;
    white-space: nowrap;
    overflow: hidden;
    text-overflow: ellipsis;
}
.lb-team {
    font-size: 0.73rem;
    color: #64748B;
    margin-top: 1px;
}
.lb-stat {
    font-family: 'Poppins', sans-serif;
    font-size: 1.1rem;
    font-weight: 800;
    color: #3B82F6;
    flex-shrink: 0;
}

/* ── MATCHUP ─────────────────────────────── */
.matchup-container {
    background: linear-gradient(135deg, #1E293B, #162032);
    border: 1px solid #334155;
    border-radius: 24px;
    padding: 2rem;
    box-shadow: 0 8px 32px rgba(0,0,0,0.4);
}
.vs-badge {
    font-family: 'Poppins', sans-serif;
    font-size: 1.8rem;
    font-weight: 900;
    color: #F97316;
    text-shadow: 0 0 20px rgba(249,115,22,0.5);
    text-align: center;
}
.matchup-player-name {
    font-family: 'Poppins', sans-serif;
    font-size: 1.1rem;
    font-weight: 700;
    color: #F1F5F9;
    text-align: center;
    margin-top: 10px;
}
.stat-bar-label {
    font-size: 0.75rem;
    font-weight: 600;
    letter-spacing: 0.08em;
    text-transform: uppercase;
    color: #64748B;
    margin-bottom: 3px;
    text-align: center;
}
.stat-bar-row {
    display: grid;
    grid-template-columns: 1fr auto 1fr;
    align-items: center;
    gap: 8px;
    margin-bottom: 14px;
}
.stat-val-left  { text-align: right; font-weight: 700; font-size: 1rem; }
.stat-val-right { text-align: left;  font-weight: 700; font-size: 1rem; }
.stat-val-win   { color: #22C55E; }
.stat-val-lose  { color: #EF4444; }

/* ── PLAYER CARDS (Query results) ────────── */
.player-card {
    background: #1E293B;
    border: 1px solid #334155;
    border-radius: 16px;
    padding: 18px 16px;
    text-align: center;
    transition: all 0.25s ease;
}
.player-card:hover {
    transform: translateY(-4px);
    border-color: #3B82F6;
    box-shadow: 0 12px 36px rgba(59,130,246,0.15);
}
.player-card-avatar {
    width: 72px; height: 72px;
    border-radius: 50%;
    object-fit: cover;
    border: 2px solid #334155;
    margin: 0 auto 10px;
    display: block;
    background: #0F172A;
}
.player-card-name {
    font-family: 'Poppins', sans-serif;
    font-size: 0.92rem;
    font-weight: 700;
    color: #F1F5F9;
    margin-bottom: 8px;
}
.player-card-stats {
    display: flex;
    justify-content: center;
    gap: 14px;
    flex-wrap: wrap;
}
.player-stat-chip {
    background: #0F172A;
    border: 1px solid #334155;
    border-radius: 8px;
    padding: 4px 10px;
    font-size: 0.75rem;
    font-weight: 600;
    color: #94A3B8;
}
.player-stat-chip span {
    color: #60A5FA;
    font-weight: 700;
}

/* ── AI SIMILARITY CARDS ─────────────────── */
.sim-card {
    background: linear-gradient(135deg, #1E293B, #162032);
    border: 1px solid #334155;
    border-radius: 18px;
    padding: 20px;
    text-align: center;
    transition: all 0.3s ease;
}
.sim-card:hover {
    transform: translateY(-5px);
    border-color: #A855F7;
    box-shadow: 0 12px 40px rgba(168,85,247,0.15);
}
.sim-rank-badge {
    font-size: 0.7rem;
    font-weight: 700;
    letter-spacing: 0.1em;
    text-transform: uppercase;
    margin-bottom: 10px;
    padding: 3px 12px;
    border-radius: 999px;
    display: inline-block;
}
.sim-rank-1 { background: rgba(245,158,11,0.15); color: #F59E0B; border: 1px solid rgba(245,158,11,0.3); }
.sim-rank-2 { background: rgba(148,163,184,0.15); color: #94A3B8; border: 1px solid rgba(148,163,184,0.3); }
.sim-rank-3 { background: rgba(180,83,9,0.15);   color: #B45309; border: 1px solid rgba(180,83,9,0.3); }
.sim-avatar {
    width: 80px; height: 80px;
    border-radius: 50%;
    object-fit: cover;
    border: 3px solid #334155;
    margin: 0 auto 12px;
    display: block;
    background: #0F172A;
}
.sim-name {
    font-family: 'Poppins', sans-serif;
    font-size: 1rem;
    font-weight: 700;
    color: #F1F5F9;
    margin-bottom: 10px;
}
.sim-bar-bg {
    background: #0F172A;
    border-radius: 999px;
    height: 8px;
    margin: 0 auto 8px;
    overflow: hidden;
    max-width: 160px;
}
.sim-bar-fill {
    height: 100%;
    border-radius: 999px;
    background: linear-gradient(90deg, #A855F7, #3B82F6);
    transition: width 0.6s ease;
}
.sim-pct {
    font-size: 1.3rem;
    font-weight: 800;
    color: #A855F7;
}
.sim-label {
    font-size: 0.72rem;
    color: #64748B;
    font-weight: 500;
    margin-top: 2px;
}

/* ── SIDEBAR ─────────────────────────────── */
.sidebar-logo {
    font-family: 'Poppins', sans-serif;
    font-size: 1.2rem;
    font-weight: 800;
    color: #F1F5F9;
    text-align: center;
    padding: 1.2rem 0 0.8rem;
    letter-spacing: -0.01em;
}
.sidebar-status {
    background: #0F172A;
    border: 1px solid #1E293B;
    border-radius: 12px;
    padding: 12px 14px;
    margin: 0.5rem 0 1rem;
    font-size: 0.8rem;
}
.status-dot-green { color: #22C55E; }
.status-dot-red   { color: #EF4444; }
.sidebar-stat {
    display: flex;
    justify-content: space-between;
    align-items: center;
    color: #64748B;
    margin-top: 5px;
    font-size: 0.78rem;
}
.sidebar-stat span { color: #94A3B8; font-weight: 600; }

/* ── TABS ────────────────────────────────── */
[data-testid="stTabs"] [data-baseweb="tab-list"] {
    background: #1E293B !important;
    border-radius: 14px !important;
    padding: 6px !important;
    gap: 4px !important;
    border: 1px solid #334155 !important;
    margin-bottom: 1.5rem !important;
}
[data-testid="stTabs"] [data-baseweb="tab"] {
    background: transparent !important;
    color: #64748B !important;
    font-weight: 600 !important;
    font-size: 0.85rem !important;
    border-radius: 10px !important;
    border: none !important;
    padding: 8px 16px !important;
    transition: all 0.2s ease !important;
    font-family: 'Inter', sans-serif !important;
}
[data-testid="stTabs"] [aria-selected="true"] {
    background: #3B82F6 !important;
    color: #FFFFFF !important;
}

/* ── STREAMLIT OVERRIDES ─────────────────── */
div[data-testid="stMetric"] {
    background: #1E293B !important;
    border: 1px solid #334155 !important;
    border-radius: 14px !important;
    padding: 16px !important;
}
[data-testid="stSelectbox"] > div,
[data-testid="stTextInput"] > div > div {
    background: #1E293B !important;
    border: 1px solid #334155 !important;
    border-radius: 10px !important;
    color: #F1F5F9 !important;
}
[data-testid="stButton"] > button {
    background: linear-gradient(135deg, #2563EB, #3B82F6) !important;
    color: white !important;
    border: none !important;
    border-radius: 10px !important;
    font-weight: 600 !important;
    transition: all 0.2s ease !important;
    font-family: 'Inter', sans-serif !important;
}
[data-testid="stButton"] > button:hover {
    transform: translateY(-2px) !important;
    box-shadow: 0 6px 20px rgba(59,130,246,0.4) !important;
}
[data-testid="stSlider"] { accent-color: #3B82F6; }
[data-testid="stDataFrame"] {
    background: #1E293B !important;
    border-radius: 12px !important;
    border: 1px solid #334155 !important;
}
[data-testid="stExpander"] {
    background: #1E293B !important;
    border: 1px solid #334155 !important;
    border-radius: 12px !important;
}
[data-testid="stExpander"] summary {
    color: #CBD5E1 !important;
    font-weight: 600 !important;
}
.stSpinner > div { border-top-color: #3B82F6 !important; }
[data-testid="stAlert"] {
    background: #1E293B !important;
    border: 1px solid #334155 !important;
    border-radius: 12px !important;
    color: #F1F5F9 !important;
}
div[data-testid="stImage"] img { border-radius: 16px; }

/* ── FULLSCREEN CHART MODE ───────────────── */
.fullscreen-chart-mode [data-testid="stSidebar"],
.fullscreen-chart-mode [data-testid="stTabs"] {
    display: none !important;
}

/* ── SCROLLBAR ───────────────────────────── */
::-webkit-scrollbar { width: 6px; height: 6px; }
::-webkit-scrollbar-track { background: #0F172A; }
::-webkit-scrollbar-thumb { background: #334155; border-radius: 3px; }
::-webkit-scrollbar-thumb:hover { background: #3B82F6; }

/* ── DIVIDER ─────────────────────────────── */
hr { border: none; border-top: 1px solid #1E293B !important; margin: 1.5rem 0 !important; }

/* ── PLOTLY CHART BG ─────────────────────── */
.js-plotly-plot .plotly .bg { fill: transparent !important; }
</style>
""", unsafe_allow_html=True)
