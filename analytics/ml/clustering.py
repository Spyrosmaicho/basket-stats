import streamlit as st
import plotly.express as px
from sklearn.preprocessing import StandardScaler
from sklearn.decomposition import PCA
from sklearn.cluster import KMeans
from ml.constants import ML_FEATURES
from charts.theme import CHART_LAYOUT, NBA_PALETTE

ARCHETYPE_NAMES = {
    0: " Scorers",
    1: " Defenders",
    2: " Playmakers",
    3: " Big Men",
    4: " All-Around",
}


def show_clustering(df):
    st.markdown(
        '<div style="font-family:Poppins,sans-serif;font-size:1rem;font-weight:600;'
        'color:#F1F5F9;margin-bottom:14px;"> Player Archetype Clustering</div>',
        unsafe_allow_html=True,
    )

    n_clusters = min(4, len(df))
    X = df[ML_FEATURES]
    scaler = StandardScaler()
    X_scaled = scaler.fit_transform(X)

    pca = PCA(n_components=2)
    pca_comp = pca.fit_transform(X_scaled)

    kmeans = KMeans(n_clusters=n_clusters, random_state=42, n_init="auto")
    clusters = kmeans.fit_predict(X_scaled)

    df_pca = df.copy()
    df_pca["PCA_X"]   = pca_comp[:, 0]
    df_pca["PCA_Y"]   = pca_comp[:, 1]
    df_pca["Cluster"] = [ARCHETYPE_NAMES.get(c, f"Group {c+1}") for c in clusters]

    explained = pca.explained_variance_ratio_
    st.markdown(
        f'<div style="color:#64748B;font-size:0.8rem;margin-bottom:12px;">'
        f'PCA explains <strong style="color:#3B82F6;">{explained[0]*100:.1f}%</strong> + '
        f'<strong style="color:#F97316;">{explained[1]*100:.1f}%</strong> of variance</div>',
        unsafe_allow_html=True,
    )

    fig = px.scatter(
        df_pca, x="PCA_X", y="PCA_Y",
        color="Cluster", hover_name="Name",
        hover_data={"Points": True, "Assists": True, "Total_Reb": True,
                    "PCA_X": False, "PCA_Y": False},
        title="Player Archetypes — AI Clustering",
        color_discrete_sequence=NBA_PALETTE,
    )
    fig.update_traces(marker=dict(size=11, line=dict(width=1, color="#0F172A")))
    fig.update_layout(
        **CHART_LAYOUT,
        xaxis_title=f"PC1 ({explained[0]*100:.1f}%)",
        yaxis_title=f"PC2 ({explained[1]*100:.1f}%)",
        legend_title="Archetype",
    )
    st.plotly_chart(fig, use_container_width=True)
