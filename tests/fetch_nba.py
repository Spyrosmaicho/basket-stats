import json
import time
from nba_api.stats.endpoints import leaguedashplayerstats

print("Fetching real NBA data from the servers... Please wait.")

time.sleep(1)

response = leaguedashplayerstats.LeagueDashPlayerStats(season='2015-16')
df = response.get_data_frames()[0]

top_players = df.sort_values(by='PTS', ascending=False).head(20)

players_array = []

for index, row in top_players.iterrows():
    player = {
        "Name": row['PLAYER_NAME'],
        "FT_Made": int(row['FTM']),
        "FT_Attempted": int(row['FTA']),
        "Two_Made": int(row['FGM']) - int(row['FG3M']),
        "Two_Attempted": int(row['FGA']) - int(row['FG3A']),
        "Three_Made": int(row['FG3M']),
        "Three_Attempted": int(row['FG3A']),
        "Off_Rebounds": int(row['OREB']),
        "Def_Rebounds": int(row['DREB']),
        "Assists": int(row['AST']),
        "Steals": int(row['STL']),
        "Blocks": int(row['BLK']),
        "Turnovers": int(row['TOV']),
        "Fouls": int(row['PF']),
        "Matches": int(row['GP']) # GP = Games Played (Matches)
    }
    players_array.append(player)

team_data = {
    "players": players_array
}

with open("nba.json", "w", encoding="utf-8") as f:
    json.dump(team_data, f, indent=4)

print("Success!")