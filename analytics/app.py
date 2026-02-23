import streamlit as st
import pandas as pd
import numpy as np
import plotly.express as px
import plotly.graph_objects as go
import warnings

# --- MACHINE LEARNING IMPORTS ---
from sklearn.preprocessing import StandardScaler
from sklearn.decomposition import PCA
from sklearn.cluster import KMeans
from sklearn.metrics.pairwise import cosine_similarity

warnings.filterwarnings('ignore')

# --- Page Configuration & Custom CSS ---
st.set_page_config(page_title="Pro Hoops Analytics", layout="wide")

st.markdown("""
    <style>
    #MainMenu {visibility: hidden;}
    footer {visibility: hidden;}
    .block-container {padding-top: 2rem;}
    div[data-testid="stMetricValue"] {
        font-size: 2rem !important;
        color: #1f77b4;
    }
    </style>
    """, unsafe_allow_html=True)

# Top Banner
st.image("https://images.unsplash.com/photo-1546519638-68e109498ffc?ixlib=rb-4.0.3&auto=format&fit=crop&w=2000&q=80", use_container_width=True)

st.title("Team Analytics Dashboard")
st.markdown("Comprehensive statistical overview, player scouting, and matchup analysis.")
st.markdown("---")

# --- Sidebar: Data Management ---
st.sidebar.image("https://images.unsplash.com/photo-1519861531473-9200262188bf?ixlib=rb-4.0.3&auto=format&fit=crop&w=500&q=80", use_container_width=True)
st.sidebar.header("Data Management")
uploaded_file = st.sidebar.file_uploader("Upload your players CSV", type=["csv"])

# --- Load Data Function ---
@st.cache_data
def load_data(file_source):
    try:
        if file_source is not None:
            df = pd.read_csv(file_source)
        else:
            # Fallback to default local file
            df = pd.read_csv('nba.csv')
        
        # Helper calculations (Common for any source)
        required_cols = ['Off_Reb', 'Def_Reb', 'Steals', 'Blocks', '2pt_A', '3pt_A', '1pt_A', 'Points']
        if all(col in df.columns for col in required_cols):
            df['Total_Reb'] = df['Off_Reb'] + df['Def_Reb']
            df['Defensive_Plays'] = df['Steals'] + df['Blocks']
            df['FGA'] = df['2pt_A'] + df['3pt_A']
            df['TS_Denom'] = 2 * (df['FGA'] + 0.44 * df['1pt_A'])
            df['TS_Pct'] = np.where(df['TS_Denom'] > 0, (df['Points'] / df['TS_Denom']) * 100, 0)
            df.fillna(0, inplace=True)
            return df
        else:
            st.sidebar.error("CSV is missing required statistical columns!")
            return pd.DataFrame()
    except FileNotFoundError:
        return pd.DataFrame()

df = load_data(uploaded_file)

if df.empty:
    st.error("Error: Dataset not found. Please upload a CSV or ensure 'nba.csv' is in the analytics folder.")
    st.stop()

# --- KPI CARDS (Highlights) ---
st.subheader("Season Highlights")
col_kpi1, col_kpi2, col_kpi3 = st.columns(3)

top_scorer = df.loc[df['Points'].idxmax()]
top_playmaker = df.loc[df['Assists'].idxmax()]
top_defender = df.loc[df['Defensive_Plays'].idxmax()]

col_kpi1.metric(label="Top Scorer", value=f"{top_scorer['Name']}", delta=f"{int(top_scorer['Points'])} Pts")
col_kpi2.metric(label="Best Playmaker", value=f"{top_playmaker['Name']}", delta=f"{int(top_playmaker['Assists'])} Ast")
col_kpi3.metric(label="Defensive Anchor", value=f"{top_defender['Name']}", delta=f"{int(top_defender['Defensive_Plays'])} Stl+Blk")

st.markdown("<br>", unsafe_allow_html=True)

# --- Tabs Configuration ---
tab1, tab2, tab3, tab4 ,tab5= st.tabs(["Interactive Charts", "Advanced Queries", "Head-to-Head Cards", "AI Scouting & Clustering","Leaderboard"])

# TAB 1: VISUAL ANALYTICS
with tab1:
    st.header("Visual Analytics")
    chart_choice = st.selectbox(
        "Select an analytical view:",
        ["Player Profiles (Radar Chart)", "Shooting Efficiency (Bubble Chart)", 
         "Scoring Volume vs Efficiency (True Shooting)", "Playmaking Efficiency (Ast vs TOs)"]
    )
    st.markdown("---")
    
    if chart_choice == "Player Profiles (Radar Chart)":
        top2 = df.sort_values(by='Points', ascending=False).head(2)
        categories = ['Points', 'Total_Reb', 'Assists', 'Steals', 'Blocks']
        fig = go.Figure()
        for index, row in top2.iterrows():
            fig.add_trace(go.Scatterpolar(r=[row['Points'], row['Total_Reb'], row['Assists'], row['Steals'], row['Blocks']], theta=categories, fill='toself', name=row['Name']))
        fig.update_layout(polar=dict(radialaxis=dict(visible=True)), showlegend=True, title=dict(text="Top 2 Scorers Comparison", font=dict(size=20)))
        st.plotly_chart(fig, use_container_width=True)
        
    elif chart_choice == "Shooting Efficiency (Bubble Chart)":
        fig = px.scatter(df[df['Points'] > 0], x="2pt %", y="3pt %", size="Points", color="Points", hover_name="Name", title="Shooting Efficiency (2PT% vs 3PT%)", size_max=40, color_continuous_scale=px.colors.sequential.Inferno)
        st.plotly_chart(fig, use_container_width=True)

    elif chart_choice == "Scoring Volume vs Efficiency (True Shooting)":
        top_5_ts = df.sort_values(by='Points', ascending=False).head(5)
        fig = go.Figure()
        fig.add_trace(go.Bar(x=top_5_ts['Name'], y=top_5_ts['Points'], name='Points (Volume)', marker_color='#17becf'))
        fig.add_trace(go.Scatter(x=top_5_ts['Name'], y=top_5_ts['TS_Pct'], name='TS% (Efficiency)', mode='markers+lines', yaxis='y2', marker=dict(color='#ff7f0e', size=10)))
        fig.update_layout(title="Scoring Volume vs Efficiency", yaxis=dict(title="Points"), yaxis2=dict(title="True Shooting %", overlaying='y', side='right'))
        st.plotly_chart(fig, use_container_width=True)

    elif chart_choice == "Playmaking Efficiency (Ast vs TOs)":
        fig = px.scatter(df, x="Turnovers", y="Assists", hover_name="Name", title="Playmaking Efficiency")
        st.plotly_chart(fig, use_container_width=True)

# TAB 2: QUERY ENGINE
with tab2:
    st.header("Database Query Engine")
    st.sidebar.markdown("### Query Filters")
    min_pts = st.sidebar.slider("Min Points", 0, int(df['Points'].max()), 0)
    min_reb = st.sidebar.slider("Min Rebounds", 0, int(df['Total_Reb'].max()), 0)
    min_ast = st.sidebar.slider("Min Assists", 0, int(df['Assists'].max()), 0)
    
    filtered_df = df[(df['Points'] >= min_pts) & (df['Total_Reb'] >= min_reb) & (df['Assists'] >= min_ast)]
    st.markdown(f"**Results: Found {len(filtered_df)} players matching criteria**")
    display_cols = ['Name', 'Points', 'Total_Reb', 'Assists', 'Steals', 'Blocks', 'Turnovers', 'Fouls', '2pt %', '3pt %']
    st.dataframe(filtered_df[display_cols], use_container_width=True, hide_index=True)
    
    csv = filtered_df[display_cols].to_csv(index=False).encode('utf-8')
    st.download_button(label="📥 Download Filtered Results as CSV", data=csv, file_name='filtered_roster.csv', mime='text/csv')

# TAB 3: HEAD-TO-HEAD
with tab3:
    st.header("Player Matchup")
    player_list = df['Name'].tolist()
    sel_col1, sel_col2 = st.columns(2)
    p1_name = sel_col1.selectbox("Select Player 1", player_list, index=0)
    p2_name = sel_col2.selectbox("Select Player 2", player_list, index=1 if len(player_list) > 1 else 0)
    
    if p1_name and p2_name:
        p1, p2 = df[df['Name'] == p1_name].iloc[0], df[df['Name'] == p2_name].iloc[0]
        st.markdown("<br>", unsafe_allow_html=True)
        h_col1, h_col2, h_col3 = st.columns([2, 1, 2])
        h_col1.markdown(f"<h3 style='text-align: right; color: #1f77b4;'>{p1['Name']}</h3>", unsafe_allow_html=True)
        h_col2.markdown("<h3 style='text-align: center; color: gray;'>VS</h3>", unsafe_allow_html=True)
        h_col3.markdown(f"<h3 style='text-align: left; color: #ff7f0e;'>{p2['Name']}</h3>", unsafe_allow_html=True)
        
        def compare_stat(stat_name, val1, val2, lower_is_better=False, is_percent=False):
            v1_str = f"{val1:.1f}%" if is_percent else str(int(val1))
            v2_str = f"{val2:.1f}%" if is_percent else str(int(val2))
            c1_color = "#2ca02c" if (val1 > val2 if not lower_is_better else val1 < val2) else "#d62728"
            c2_color = "#2ca02c" if (val2 > val1 if not lower_is_better else val2 < val1) else "#d62728"
            if val1 == val2: c1_color = c2_color = "gray"
            
            col_a, col_b, col_c = st.columns([2, 1, 2])
            col_a.markdown(f"<h4 style='text-align: right; color: {c1_color}; margin:0;'>{v1_str}</h4>", unsafe_allow_html=True)
            col_b.markdown(f"<p style='text-align: center; font-weight: bold; margin:0; color: white;'>{stat_name}</p>", unsafe_allow_html=True)
            col_c.markdown(f"<h4 style='text-align: left; color: {c2_color}; margin:0;'>{v2_str}</h4>", unsafe_allow_html=True)
            st.markdown("<br>", unsafe_allow_html=True)

        stats_to_comp = [("Points", "Points"), ("Rebounds", "Total_Reb"), ("Assists", "Assists"), ("Steals", "Steals"), ("Blocks", "Blocks")]
        for label, col in stats_to_comp:
            compare_stat(label, p1[col], p2[col])

# TAB 4: AI SCOUTING
with tab4:
    #st.header("🤖 AI Scouting & Clustering Engine")
    ml_features = ['Points', 'Total_Reb', 'Assists', 'Steals', 'Blocks', 'Turnovers', '2pt %', '3pt %']
    X = df[ml_features]
    scaler = StandardScaler()
    X_scaled = scaler.fit_transform(X)
    
    # Similarity
    target_player = st.selectbox("Select Target Player for Twin Search:", df['Name'].tolist())
    if target_player:
        sim_matrix = cosine_similarity(X_scaled)
        p_idx = df.index[df['Name'] == target_player].tolist()[0]
        df_sim = df.copy()
        df_sim['Similarity_Score'] = sim_matrix[p_idx] * 100
        top_sim = df_sim[df_sim['Name'] != target_player].sort_values('Similarity_Score', ascending=False).head(3)
        cols = st.columns(3)
        for i, (idx, row) in enumerate(top_sim.iterrows()):
            cols[i].metric(label=f"Match #{i+1}", value=row['Name'], delta=f"{row['Similarity_Score']:.1f}% Match")
    
    st.markdown("---")
    # PCA & Clustering
    pca = PCA(n_components=2)
    pca_comp = pca.fit_transform(X_scaled)
    kmeans = KMeans(n_clusters=min(3, len(df)), random_state=42)
    clusters = kmeans.fit_predict(X_scaled)
    df_pca = df.copy()
    df_pca['PCA_X'], df_pca['PCA_Y'], df_pca['Cluster'] = pca_comp[:, 0], pca_comp[:, 1], [f"Group {c+1}" for c in clusters]
    
    fig_ml = px.scatter(df_pca, x='PCA_X', y='PCA_Y', color='Cluster', hover_name='Name', title="Player Archetypes mapped by AI")
    st.plotly_chart(fig_ml, use_container_width=True)

with tab5:
    st.header("Team Leaderboards")
    l_col1, l_col2, l_col3 = st.columns(3)
    
    # Top 5 Scorers
    with l_col1:
        st.subheader("Top Scorers")
        top_5_pts = df.sort_values('Points', ascending=False).head(5)[['Name', 'Points']]
        st.table(top_5_pts)
        
    # Top 5 Playmakers
    with l_col2:
        st.subheader("Top Playmakers")
        top_5_ast = df.sort_values('Assists', ascending=False).head(5)[['Name', 'Assists']]
        st.table(top_5_ast)
        
    # Top 5 Defenders
    with l_col3:
        st.subheader("Defensive Leaders")
        top_5_def = df.sort_values('Defensive_Plays', ascending=False).head(5)[['Name', 'Defensive_Plays']]
        # Μετονομασία για να φαίνεται ωραία στον πίνακα
        top_5_def.columns = ['Name', 'Stl + Blk']
        st.table(top_5_def)    