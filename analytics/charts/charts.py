import streamlit as st
import plotly.express as px
import plotly.graph_objects as go
from charts.theme import CHART_LAYOUT, NBA_PALETTE


def show_charts(df):
    st.markdown(
        '<div class="section-header"><span class="section-dot"></span> Visual Analytics</div>',
        unsafe_allow_html=True,
    )

    # ── Full-screen mode toggle ──────────────────
    if "fullscreen_chart" not in st.session_state:
        st.session_state.fullscreen_chart = False

    if st.session_state.fullscreen_chart:
        _show_fullscreen(df)
        return

    chart_choice = st.selectbox(
        "Select an analytical view:",
        [
            "  Player Profiles — Radar Chart",
            "  Shooting Efficiency — Bubble Chart",
            "  Scoring Volume vs Efficiency",
            "  Playmaking Efficiency — Ast vs TOs",
        ],
    )

    col_btn, _ = st.columns([1, 5])
    with col_btn:
        if st.button("⛶  Full Screen", use_container_width=True):
            st.session_state.fullscreen_chart = True
            st.session_state.current_chart = chart_choice
            st.rerun()

    st.markdown("---")
    _render_chart(chart_choice, df)


def _render_chart(choice: str, df):
    if "Radar" in choice:
        _radar(df)
    elif "Bubble" in choice:
        _bubble(df)
    elif "Volume" in choice:
        _volume_efficiency(df)
    elif "Playmaking" in choice:
        _playmaking(df)


def _show_fullscreen(df):
    col_back, col_title = st.columns([1, 8])
    with col_back:
        if st.button("← Back"):
            st.session_state.fullscreen_chart = False
            st.rerun()
    with col_title:
        st.markdown(
            f'<div style="color:#94A3B8;font-size:0.9rem;padding-top:8px;">'
            f'{st.session_state.get("current_chart","Chart")}</div>',
            unsafe_allow_html=True,
        )
    st.markdown("<br>", unsafe_allow_html=True)
    _render_chart(st.session_state.get("current_chart", "Radar"),df)


# ── Individual charts ──────────────────────────

def _radar(df):

    import plotly.graph_objects as go
    import streamlit as st

    top2 = df.sort_values("Points", ascending=False).head(2)

    categories = ["Points", "Total_Reb", "Assists", "Steals", "Blocks"]

    colors = ["#3B82F6", "#EF4444"] 

    fig = go.Figure()

    for i, (_, row) in enumerate(top2.iterrows()):

        color = colors[i % len(colors)]

        if color.startswith("#"):
            r, g, b = int(color[1:3], 16), int(color[3:5], 16), int(color[5:7], 16)
            fill_col = f"rgba({r}, {g}, {b}, 0.15)"

        elif color.startswith("rgb"):
            fill_col = color.replace(")", ", 0.15)").replace("rgb", "rgba")

        else:
            fill_col = color

        fig.add_trace(
            go.Scatterpolar(
                r=[row[c] for c in categories],
                theta=categories,
                fill="toself",
                name=row["Name"],
                line_color=color,
                fillcolor=fill_col
            )
        )

    layout = dict(
        title="Top 2 Scorers — Skill Radar",
        polar=dict(
            bgcolor="#0F172A",
            radialaxis=dict(
                visible=True,
                gridcolor="#1E293B",
                tickfont=dict(color="#64748B"),
            ),
            angularaxis=dict(
                gridcolor="#1E293B",
                tickfont=dict(color="#94A3B8"),
            ),
        ),
    )

    fig.update_layout(**layout)

    st.plotly_chart(fig, use_container_width=True)

def _bubble(df):
    data = df[df["Points"] > 0]
    fig = px.scatter(
        data,
        x="2pt %",
        y="3pt %",
        size="Points",
        color="Points",
        hover_name="Name",
        title="Shooting Efficiency — 2PT% vs 3PT%",
        size_max=45,
        color_continuous_scale="Blues",
    )
    fig.update_layout(**CHART_LAYOUT)
    fig.update_traces(
        marker=dict(line=dict(width=1, color="#334155")),
        hovertemplate="<b>%{hovertext}</b><br>2PT%%: %{x:.1f}<br>3PT%%: %{y:.1f}<br>PTS: %{marker.size}<extra></extra>",
    )
    st.plotly_chart(fig, use_container_width=True)


def _volume_efficiency(df):
    top5 = df.sort_values("Points", ascending=False).head(5)

    fig = go.Figure()

    fig.add_trace(
        go.Bar(
            x=top5["Name"],
            y=top5["Points"],
            name="Points",
            marker=dict(
                color=NBA_PALETTE[:len(top5)],
                line=dict(width=0),
            ),
        )
    )

    fig.add_trace(
        go.Scatter(
            x=top5["Name"],
            y=top5["2pt %"],
            name="2PT %",
            mode="markers+lines",
            yaxis="y2",
            marker=dict(color="#F97316", size=10, symbol="diamond"),
            line=dict(color="#F97316", width=2, dash="dot"),
        )
    )

    layout = CHART_LAYOUT.copy()

    # override ONLY what you need
    layout.update({
        "title": "Scoring Volume vs 2PT Efficiency",
        "yaxis": dict(title="Points", gridcolor="#1E293B"),
        "yaxis2": dict(
            title="2PT %",
            overlaying="y",
            side="right",
            gridcolor="#1E293B",
        ),
        "barmode": "group",
    })

    fig.update_layout(layout)

    st.plotly_chart(fig, use_container_width=True)


def _playmaking(df):
    fig = px.scatter(
        df,
        x="Turnovers",
        y="Assists",
        hover_name="Name",
        color="Assists",
        size="Assists",
        size_max=30,
        title="Playmaking Efficiency — Assists vs Turnovers",
        color_continuous_scale="Blues",
    )
    # Add quadrant line
    mid_ast = df["Assists"].median()
    mid_to  = df["Turnovers"].median()
    fig.add_hline(y=mid_ast, line=dict(color="#334155", dash="dot"), opacity=0.6)
    fig.add_vline(x=mid_to,  line=dict(color="#334155", dash="dot"), opacity=0.6)
    fig.update_layout(**CHART_LAYOUT)
    st.plotly_chart(fig, use_container_width=True)
