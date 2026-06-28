from utils.images import get_player_image_url


def render_kpi_card(label: str, player_name: str, value: str, unit: str, accent: str) -> str:
    img = get_player_image_url(player_name)
    short = player_name if len(player_name) <= 18 else player_name[:16] + "…"
    return f"""
<div class="kpi-card {accent}">
  <div class="kpi-label">{label}</div>
  <img class="kpi-avatar" src="{img}"
       onerror="this.src='https://cdn-icons-png.flaticon.com/512/847/847969.png'" />
  <div class="kpi-name">{short}</div>
  <div class="kpi-value">{value}</div>
  <div class="kpi-unit">{unit}</div>
</div>
"""
