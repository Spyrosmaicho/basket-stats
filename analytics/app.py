import streamlit as st
import pandas as pd
import numpy as np
import plotly.express as px
import plotly.graph_objects as go
import warnings

# --- NEW MACHINE LEARNING IMPORTS ---
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

st.image("https://images.unsplash.com/photo-1546519638-68e109498ffc?ixlib=rb-4.0.3&auto=format&fit=crop&w=2000&q=80", use_container_width=True)

st.title("Team Analytics Dashboard")
st.markdown("Comprehensive statistical overview, player scouting, and matchup analysis.")
st.markdown("---")

# --- Load Data ---
@st.cache_data
def load_data():
    try:
        df = pd.read_csv('nba.csv')
        df['Total_Reb'] = df['Off_Reb'] + df['Def_Reb']
        df['Defensive_Plays'] = df['Steals'] + df['Blocks']
        df['FGA'] = df['2pt_A'] + df['3pt_A']
        df['TS_Denom'] = 2 * (df['FGA'] + 0.44 * df['1pt_A'])
        df['TS_Pct'] = np.where(df['TS_Denom'] > 0, (df['Points'] / df['TS_Denom']) * 100, 0)
        df.fillna(0, inplace=True)
        return df
    except FileNotFoundError:
        return pd.DataFrame()

df = load_data()

if df.empty:
    st.error("Error: 'players.csv' not found. Please run the C backend first and export the data.")
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

tab1, tab2, tab3, tab4 = st.tabs(["Interactive Charts", "Advanced Queries", "Head-to-Head Cards", "🤖 AI Scouting & Clustering"])

#  SELECTABLE CHARTS
with tab1:
    st.header("Visual Analytics")
    
    chart_choice = st.selectbox(
        "Select an analytical view:",
        [
            "Player Profiles (Radar Chart)", 
            "Shooting Efficiency (Bubble Chart)", 
            "Scoring Volume vs Efficiency (True Shooting)",
            "Playmaking Efficiency (Ast vs TOs)"
        ]
    )
    
    st.markdown("---")
    
    if chart_choice == "Player Profiles (Radar Chart)":
        top2 = df.sort_values(by='Points', ascending=False).head(2)
        categories = ['Points', 'Total_Reb', 'Assists', 'Steals', 'Blocks']
        
        fig = go.Figure()
        for index, row in top2.iterrows():
            fig.add_trace(go.Scatterpolar(
                r=[row['Points'], row['Total_Reb'], row['Assists'], row['Steals'], row['Blocks']],
                theta=categories,
                fill='toself',
                name=row['Name']
            ))
            
        fig.update_layout(
            polar=dict(radialaxis=dict(visible=True)),
            showlegend=True,
            title=dict(text="Top 2 Scorers Comparison", font=dict(size=20))
        )
        st.plotly_chart(fig, use_container_width=True)
        
    elif chart_choice == "Shooting Efficiency (Bubble Chart)":
        fig = px.scatter(
            df[df['Points'] > 0], 
            x="2pt %", 
            y="3pt %", 
            size="Points", 
            color="Points",
            hover_name="Name", 
            title="Shooting Efficiency (2PT% vs 3PT%)",
            labels={"2pt %": "2-Point Percentage (%)", "3pt %": "3-Point Percentage (%)"},
            size_max=40,
            color_continuous_scale=px.colors.sequential.Inferno
        )
        st.plotly_chart(fig, use_container_width=True)

    elif chart_choice == "Scoring Volume vs Efficiency (True Shooting)":
        top_5_ts = df.sort_values(by='Points', ascending=False).head(5)
        
        fig = go.Figure()
        fig.add_trace(go.Bar(
            x=top_5_ts['Name'], 
            y=top_5_ts['Points'], 
            name='Points (Volume)',
            marker_color='#17becf'
        ))
        fig.add_trace(go.Scatter(
            x=top_5_ts['Name'], 
            y=top_5_ts['TS_Pct'], 
            name='TS% (Efficiency)',
            mode='lines+markers',
            marker=dict(size=10, color='#ff7f0e'),
            line=dict(width=3),
            yaxis='y2'
        ))
        
        fig.update_layout(
            title=dict(text="Scoring Volume vs True Shooting Efficiency", font=dict(size=20)),
            yaxis=dict(title=dict(text='Total Points', font=dict(color='#17becf')), tickfont=dict(color='#17becf')),
            yaxis2=dict(title=dict(text='True Shooting %', font=dict(color='#ff7f0e')), tickfont=dict(color='#ff7f0e'), overlaying='y', side='right'),
            legend=dict(x=0.01, y=0.99)
        )
        st.plotly_chart(fig, use_container_width=True)
        
    elif chart_choice == "Playmaking Efficiency (Ast vs TOs)":
        fig = px.scatter(
            df, 
            x="Turnovers", 
            y="Assists", 
            hover_name="Name",
            title="Playmaking Efficiency (Ast vs TOs)",
            labels={"Turnovers": "Turnovers (Bad)", "Assists": "Assists (Good)"},
            color_discrete_sequence=['#e377c2']
        )
        fig.update_traces(marker=dict(size=12, line=dict(width=1, color='DarkSlateGrey')))
        
        max_val = max(df['Turnovers'].max(), df['Assists'].max())
        if pd.notna(max_val) and max_val > 0:
            fig.add_shape(type="line", x0=0, y0=0, x1=max_val, y1=max_val, line=dict(color="gray", width=2, dash="dash"))
            
        st.plotly_chart(fig, use_container_width=True)


# QUERY ENGINE
 
with tab2:
    st.header("Database Query Engine")
    
    st.sidebar.image("https://images.unsplash.com/photo-1519861531473-9200262188bf?ixlib=rb-4.0.3&auto=format&fit=crop&w=500&q=80", use_container_width=True)
    st.sidebar.markdown("### Query Filters")
    st.sidebar.write("Adjust the sliders below to filter the main table.")
    
    min_pts = st.sidebar.slider("Min Points", 0, int(df['Points'].max()) if not df.empty else 100, 0)
    min_reb = st.sidebar.slider("Min Rebounds", 0, int(df['Total_Reb'].max()) if not df.empty else 50, 0)
    min_ast = st.sidebar.slider("Min Assists", 0, int(df['Assists'].max()) if not df.empty else 20, 0)
    min_stl = st.sidebar.slider("Min Steals", 0, int(df['Steals'].max()) if not df.empty else 10, 0)
    min_blk = st.sidebar.slider("Min Blocks", 0, int(df['Blocks'].max()) if not df.empty else 10, 0)
    max_tov = st.sidebar.slider("Max Turnovers Allowed", 0, int(df['Turnovers'].max()) if not df.empty else 20, int(df['Turnovers'].max()) if not df.empty else 20)
    
    filtered_df = df[
        (df['Points'] >= min_pts) &
        (df['Total_Reb'] >= min_reb) &
        (df['Assists'] >= min_ast) &
        (df['Steals'] >= min_stl) &
        (df['Blocks'] >= min_blk) &
        (df['Turnovers'] <= max_tov)
    ]
    
    st.markdown(f"**Results: Found {len(filtered_df)} players matching your criteria**")
    
    display_cols = ['Name', 'Points', 'Total_Reb', 'Assists', 'Steals', 'Blocks', 'Turnovers', 'Fouls', '2pt %', '3pt %']
    st.dataframe(filtered_df[display_cols], use_container_width=True, hide_index=True)
    
    csv = filtered_df[display_cols].to_csv(index=False).encode('utf-8')
    st.download_button(
        label="📥 Download Filtered Results as CSV",
        data=csv,
        file_name='filtered_roster.csv',
        mime='text/csv',
    )


# HEAD-TO-HEAD
with tab3:
    st.header("Player Matchup")
    
    player_list = df['Name'].tolist()
    
    sel_col1, sel_col2 = st.columns(2)
    p1_name = sel_col1.selectbox("Select Player 1", player_list, index=0)
    p2_name = sel_col2.selectbox("Select Player 2", player_list, index=1 if len(player_list) > 1 else 0)
    
    if p1_name and p2_name:
        p1 = df[df['Name'] == p1_name].iloc[0]
        p2 = df[df['Name'] == p2_name].iloc[0]
        
        st.markdown("<br>", unsafe_allow_html=True)
        
        h_col1, h_col2, h_col3 = st.columns([2, 1, 2])
        h_col1.markdown(f"<h3 style='text-align: right; color: #1f77b4;'>{p1['Name']}</h3>", unsafe_allow_html=True)
        h_col2.markdown("<h3 style='text-align: center; color: gray;'>VS</h3>", unsafe_allow_html=True)
        h_col3.markdown(f"<h3 style='text-align: left; color: #ff7f0e;'>{p2['Name']}</h3>", unsafe_allow_html=True)
        
        st.markdown("<hr style='margin-top: 0px; margin-bottom: 20px;'>", unsafe_allow_html=True)
        
        def compare_stat(stat_name, val1, val2, lower_is_better=False, is_percent=False):
            v1_str = f"{val1:.1f}%" if is_percent else str(int(val1))
            v2_str = f"{val2:.1f}%" if is_percent else str(int(val2))
            
            color_win = "#2ca02c"
            color_lose = "#d62728"
            color_tie = "gray"
            
            c1_color, c2_color = color_tie, color_tie
            
            if val1 != val2:
                p1_wins = (val1 < val2) if lower_is_better else (val1 > val2)
                if p1_wins:
                    c1_color, c2_color = color_win, color_lose
                else:
                    c1_color, c2_color = color_lose, color_win

            col_a, col_b, col_c = st.columns([2, 1, 2])
            col_a.markdown(f"<h4 style='text-align: right; color: {c1_color}; margin:0;'>{v1_str}</h4>", unsafe_allow_html=True)
            col_b.markdown(f"<p style='text-align: center; font-weight: bold; margin:0; color: white;'>{stat_name}</p>", unsafe_allow_html=True)
            col_c.markdown(f"<h4 style='text-align: left; color: {c2_color}; margin:0;'>{v2_str}</h4>", unsafe_allow_html=True)
            st.markdown("<br>", unsafe_allow_html=True)

        compare_stat("Points", p1['Points'], p2['Points'])
        compare_stat("Rebounds", p1['Total_Reb'], p2['Total_Reb'])
        compare_stat("Assists", p1['Assists'], p2['Assists'])
        compare_stat("Steals", p1['Steals'], p2['Steals'])
        compare_stat("Blocks", p1['Blocks'], p2['Blocks'])
        compare_stat("Turnovers", p1['Turnovers'], p2['Turnovers'], lower_is_better=True)
        compare_stat("Fouls", p1['Fouls'], p2['Fouls'], lower_is_better=True)
        compare_stat("2PT Accuracy", p1['2pt %'], p2['2pt %'], is_percent=True)
        compare_stat("3PT Accuracy", p1['3pt %'], p2['3pt %'], is_percent=True)


# AI SCOUTING & CLUSTERING
with tab4:
    #st.header("🤖 AI Scouting & Clustering Engine")
    #st.write("Using advanced Machine Learning algorithms (PCA, K-Means, Cosine Similarity) to discover hidden player patterns.")
    
    # Preprocessing Data for Machine Learning
    ml_features = ['Points', 'Total_Reb', 'Assists', 'Steals', 'Blocks', 'Turnovers', '2pt %', '3pt %']
    X = df[ml_features]
    
    # Standardize features (Mean=0, Variance=1) so large numbers like Points don't dominate Steals
    scaler = StandardScaler()
    X_scaled = scaler.fit_transform(X)
    
    st.markdown("---")
    
    # 1. Similarity Engine (Cosine Similarity)
    st.subheader("1. AI Player Similarity Engine")
    st.write("Select a player to find their statistical 'twins' across the league.")
    
    target_player = st.selectbox("Select Target Player:", df['Name'].tolist())
    
    if target_player:
        # Calculate cosine similarity matrix for all players
        similarity_matrix = cosine_similarity(X_scaled)
        
        # Get index of selected player
        player_idx = df.index[df['Name'] == target_player].tolist()[0]
        
        # Get similarity scores for this player
        player_similarities = similarity_matrix[player_idx]
        
        # Add scores to dataframe to sort them
        df_sim = df.copy()
        df_sim['Similarity_Score'] = player_similarities * 100 
        
        # Sort and get top 3 similar players (excluding the player himself)
        top_similar = df_sim[df_sim['Name'] != target_player].sort_values('Similarity_Score', ascending=False).head(3)
        
        sim_col1, sim_col2, sim_col3 = st.columns(3)
        cols = [sim_col1, sim_col2, sim_col3]
        
        for i, (index, row) in enumerate(top_similar.iterrows()):
            cols[i].metric(label=f"Match #{i+1}", value=row['Name'], delta=f"{row['Similarity_Score']:.1f}% Match")

    st.markdown("---")
    
    # 2. Player Archetypes (PCA + K-Means)
    st.subheader("2. AI Player Archetype Clustering")
    st.write("The AI compresses 8 statistical categories into 2 dimensions (PCA) and automatically groups players into distinct archetypes (K-Means).")
    
    # Reduce dimensions from 8 stats to 2 (X and Y coordinates)
    pca = PCA(n_components=2)
    pca_components = pca.fit_transform(X_scaled)
    
    # Determine clusters (K-Means). We use 3 clusters dynamically based on our dataset size
    num_clusters = min(3, len(df))
    kmeans = KMeans(n_clusters=num_clusters, random_state=42)
    clusters = kmeans.fit_predict(X_scaled)
    
    # Add results back to a new dataframe for plotting
    df_pca = df.copy()
    df_pca['PCA_X'] = pca_components[:, 0]
    df_pca['PCA_Y'] = pca_components[:, 1]
    df_pca['Archetype_Cluster'] = [f"Archetype Group {c+1}" for c in clusters]
    
    # Create an interactive scatter plot
    fig_ml = px.scatter(
        df_pca,
        x='PCA_X', 
        y='PCA_Y',
        color='Archetype_Cluster',
        hover_name='Name',
        hover_data=['Points', 'Total_Reb', 'Assists'],
        title="Player Archetypes mapped by AI",
        labels={'PCA_X': 'Offensive/Playmaking Dimension (PCA 1)', 'PCA_Y': 'Defensive/Efficiency Dimension (PCA 2)'}
    )
    
    fig_ml.update_traces(marker=dict(size=14, line=dict(width=2, color='DarkSlateGrey')))
    st.plotly_chart(fig_ml, use_container_width=True)