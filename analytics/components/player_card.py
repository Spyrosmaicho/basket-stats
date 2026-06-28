from utils.images import get_player_image_url


def render_player_card(row) -> str:
    img = get_player_image_url(row["Name"])
    name = row["Name"] if len(row["Name"]) <= 18 else row["Name"][:16] + "…"
    return f"""
<div class="player-card">
  <img class="player-card-avatar" src="{img}"
       onerror="this.src='https://cdn-icons-png.flaticon.com/512/847/847969.png'" />
  <div class="player-card-name">{name}</div>
  <div class="player-card-stats">
    <div class="player-stat-chip">PTS <span>{int(row['Points'])}</span></div>
    <div class="player-stat-chip">REB <span>{int(row['Total_Reb'])}</span></div>
    <div class="player-stat-chip">AST <span>{int(row['Assists'])}</span></div>
    <div class="player-stat-chip">STL <span>{int(row['Steals'])}</span></div>
    <div class="player-stat-chip">BLK <span>{int(row['Blocks'])}</span></div>
    <div class="player-stat-chip">2PT <span>{row['2pt %']:.0f}%</span></div>
    <div class="player-stat-chip">3PT <span>{row['3pt %']:.0f}%</span></div>
  </div>
</div>
"""
