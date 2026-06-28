import streamlit as st
from sklearn.preprocessing import StandardScaler
from sklearn.metrics.pairwise import cosine_similarity
from ml.constants import ML_FEATURES
from components.sim_card import render_sim_card
from utils.images import get_player_image_url


def show_similarity(df):
    st.markdown(
        '<div style="font-family:Poppins,sans-serif;font-size:1rem;font-weight:600;'
        'color:#F1F5F9;margin-bottom:14px;">🔍 Statistical Twin Finder</div>',
        unsafe_allow_html=True,
    )

    target = st.selectbox("Select target player:", df["Name"].tolist(), key="sim_target")

    X = df[ML_FEATURES]
    scaler = StandardScaler()
    X_scaled = scaler.fit_transform(X)
    sim_matrix = cosine_similarity(X_scaled)

    p_idx = df.index[df["Name"] == target].tolist()[0]
    df_sim = df.copy()
    df_sim["Similarity_Score"] = sim_matrix[p_idx] * 100
    top3 = (
        df_sim[df_sim["Name"] != target]
        .sort_values("Similarity_Score", ascending=False)
        .head(3)
    )

    target_img = get_player_image_url(target)
    st.markdown(
        f"""
<div style="text-align:center;margin-bottom:1.5rem;">
  <img src="{target_img}" style="width:90px;height:90px;border-radius:50%;
    object-fit:cover;border:3px solid #3B82F6;background:#0F172A;"
    onerror="this.src='{get_player_image_url('')}'" />
  <div style="font-family:Poppins,sans-serif;font-weight:700;font-size:1.1rem;
    color:#F1F5F9;margin-top:8px;">{target}</div>
  <div style="color:#64748B;font-size:0.78rem;">Statistical Profile</div>
</div>
""",
        unsafe_allow_html=True,
    )

    cols = st.columns(3)
    for i, (col, (_, row)) in enumerate(zip(cols, top3.iterrows())):
        with col:
            st.markdown(
                render_sim_card(i, row["Name"], row["Similarity_Score"]),
                unsafe_allow_html=True,
            )
