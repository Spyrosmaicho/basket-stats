import streamlit as st


def show_hero():
    st.markdown(
        """
<div class="hero-section">
  <div class="hero-badge"> Sports Analytics Platform</div>
  <div class="hero-title">Pro Hoops Analytics</div>
  <div class="hero-subtitle">
    Professional Basketball Intelligence — powered by a custom C engine
  </div>
  <div class="hero-pills">
    <div class="hero-pill"><span></span>C Engine</div>
    <div class="hero-pill"><span></span>SQLite</div>
    <div class="hero-pill"><span></span>Machine Learning</div>
    <div class="hero-pill"><span></span>Interactive Dashboards</div>
    <div class="hero-pill"><span></span>Live NBA Data</div>
  </div>
</div>
""",
        unsafe_allow_html=True,
    )
