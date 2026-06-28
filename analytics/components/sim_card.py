from utils.images import get_player_image_url

_RANK_LABELS = [
    ("sim-rank-1", " Best Match"),
    ("sim-rank-2", " 2nd Match"),
    ("sim-rank-3", " 3rd Match"),
]


def render_sim_card(rank_idx: int, name: str, score: float) -> str:
    img = get_player_image_url(name)
    cls, badge = _RANK_LABELS[rank_idx]
    bar_width = min(int(score), 100)
    if score >= 97:
        label = "Virtually Identical"
    elif score >= 92:
        label = "Very Similar"
    elif score >= 85:
        label = "Similar"
    else:
        label = "Moderate Match"
    return f"""
<div class="sim-card">
  <div class="{cls} sim-rank-badge">{badge}</div>
  <img class="sim-avatar" src="{img}"
       onerror="this.src='https://cdn-icons-png.flaticon.com/512/847/847969.png'" />
  <div class="sim-name">{name}</div>
  <div class="sim-bar-bg">
    <div class="sim-bar-fill" style="width:{bar_width}%;"></div>
  </div>
  <div class="sim-pct">{score:.1f}%</div>
  <div class="sim-label">{label}</div>
</div>
"""
