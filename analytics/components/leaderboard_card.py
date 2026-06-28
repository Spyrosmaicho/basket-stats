from utils.images import get_player_image_url

_RANK_META = [
    ("1", "gold"),
    ("2", "silver"),
    ("3", "bronze"),
    ("4",  "other"),
    ("5",  "other"),
]


def render_leaderboard_card(rank_idx: int, name: str, stat_value, stat_label: str) -> str:
    symbol, cls = _RANK_META[rank_idx] if rank_idx < len(_RANK_META) else ("#", "other")
    img = get_player_image_url(name)
    short = name if len(name) <= 20 else name[:18] + "…"
    val = float(stat_value)
    val_str = f"{int(val)}" if val == int(val) else f"{val:.1f}"
    return f"""
<div class="lb-card">
  <div class="lb-rank {cls}">{symbol}</div>
  <img class="lb-avatar" src="{img}"
       onerror="this.src='https://cdn-icons-png.flaticon.com/512/847/847969.png'" />
  <div class="lb-info">
    <div class="lb-name">{short}</div>
    <div class="lb-team">{stat_label}</div>
  </div>
  <div class="lb-stat">{val_str}</div>
</div>
"""
