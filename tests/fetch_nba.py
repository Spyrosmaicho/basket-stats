import json
import random
import requests
import urllib3
import pandas as pd
from nba_api.stats.endpoints import leaguedashplayerstats
import sys

urllib3.disable_warnings(urllib3.exceptions.InsecureRequestWarning)

import time 

def get_nba_fallback(limit):
    backup_players = [
        {"Name": "Luka Doncic", "FT_Made": 380, "FT_Attempted": 485, "Two_Made": 410, "Two_Attempted": 720, "Three_Made": 185, "Three_Attempted": 490, "Off_Rebounds": 50, "Def_Rebounds": 450, "Assists": 520, "Steals": 80, "Blocks": 30, "Turnovers": 210, "Fouls": 110, "Matches": 55},
        {"Name": "Shai Gilgeous-Alexander", "FT_Made": 400, "FT_Attempted": 450, "Two_Made": 480, "Two_Attempted": 850, "Three_Made": 80, "Three_Attempted": 220, "Off_Rebounds": 45, "Def_Rebounds": 250, "Assists": 350, "Steals": 120, "Blocks": 45, "Turnovers": 130, "Fouls": 125, "Matches": 58},
        {"Name": "Giannis Antetokounmpo", "FT_Made": 350, "FT_Attempted": 530, "Two_Made": 550, "Two_Attempted": 880, "Three_Made": 25, "Three_Attempted": 95, "Off_Rebounds": 150, "Def_Rebounds": 510, "Assists": 360, "Steals": 65, "Blocks": 60, "Turnovers": 180, "Fouls": 150, "Matches": 56},
        {"Name": "Nikola Jokic", "FT_Made": 250, "FT_Attempted": 300, "Two_Made": 460, "Two_Attempted": 750, "Three_Made": 70, "Three_Attempted": 190, "Off_Rebounds": 160, "Def_Rebounds": 560, "Assists": 500, "Steals": 75, "Blocks": 50, "Turnovers": 160, "Fouls": 140, "Matches": 57},
        {"Name": "Jayson Tatum", "FT_Made": 290, "FT_Attempted": 350, "Two_Made": 310, "Two_Attempted": 610, "Three_Made": 160, "Three_Attempted": 420, "Off_Rebounds": 55, "Def_Rebounds": 410, "Assists": 280, "Steals": 55, "Blocks": 35, "Turnovers": 140, "Fouls": 110, "Matches": 56}
    ]
    return backup_players[:limit]


def get_nba_data(limit=25):
    print(f" Fetching Top {limit} NBA players ...")
    
    custom_headers = {
        'Host': 'stats.nba.com',
        'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/122.0.0.0 Safari/537.36',
        'Accept': 'application/json, text/plain, */*',
        'Accept-Language': 'en-US,en;q=0.9',
        'Referer': 'https://www.nba.com/',
        'Origin': 'https://www.nba.com',
        'Connection': 'keep-alive',
    }

    for attempt in range(3): 
        try:
            print(f" Attempt {attempt + 1}/3...")
            response = leaguedashplayerstats.LeagueDashPlayerStats(
                season='2024-25',
                headers=custom_headers,
                timeout=20 
            )
            
            df = response.get_data_frames()[0]
            top_players = df.sort_values(by='PTS', ascending=False).head(limit)
            
            players_array = []
            for _, row in top_players.iterrows():
                player = {
                    "Name": f"{row['PLAYER_NAME']}",
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
                    "Matches": int(row['GP'])
                }
                players_array.append(player)
                
            return players_array
            
        except Exception as e:
            print(f" Error on attempt {attempt + 1}: {e}")
            time.sleep(3) 

    print("\n NBA API is currently blocking requests.")
    print(" Deploying Backup Roster to keep the pipeline alive...")
    return get_nba_fallback(limit)

def get_euroleague_random_25():
    print(" Selecting 25 random Euroleague stars from the database...")
    

    all_100 = [
    {"Name": "Sasha Vezenkov", "GP": 38, "FTM": 163, "FTA": 186, "2PM": 144, "2PA": 224, "3PM": 72, "3PA": 186, "OR": 72, "DR": 178, "AST": 68, "STL": 34, "BLK": 8, "TOV": 49, "PF": 129},
    {"Name": "Tj Shorts", "GP": 37, "FTM": 151, "FTA": 207, "2PM": 229, "2PA": 444, "3PM": 29, "3PA": 81, "OR": 18, "DR": 77, "AST": 270, "STL": 37, "BLK": 3, "TOV": 85, "PF": 148},
    {"Name": "Nikola Mirotic", "GP": 30, "FTM": 150, "FTA": 168, "2PM": 99, "2PA": 180, "3PM": 60, "3PA": 156, "OR": 54, "DR": 138, "AST": 60, "STL": 30, "BLK": 9, "TOV": 54, "PF": 120},
    {"Name": "Theo Maledon", "GP": 33, "FTM": 207, "FTA": 231, "2PM": 92, "2PA": 178, "3PM": 56, "3PA": 158, "OR": 13, "DR": 99, "AST": 151, "STL": 33, "BLK": 6, "TOV": 59, "PF": 132},
    {"Name": "Zach Leday", "GP": 34, "FTM": 163, "FTA": 176, "2PM": 108, "2PA": 204, "3PM": 54, "3PA": 119, "OR": 23, "DR": 129, "AST": 40, "STL": 23, "BLK": 3, "TOV": 44, "PF": 136},
    {"Name": "Kendrick Nunn", "GP": 40, "FTM": 120, "FTA": 136, "2PM": 176, "2PA": 316, "3PM": 108, "3PA": 280, "OR": 32, "DR": 108, "AST": 168, "STL": 40, "BLK": 8, "TOV": 112, "PF": 160},
    {"Name": "Chima Moneke", "GP": 33, "FTM": 125, "FTA": 155, "2PM": 112, "2PA": 171, "3PM": 39, "3PA": 128, "OR": 72, "DR": 128, "AST": 75, "STL": 29, "BLK": 9, "TOV": 59, "PF": 132},
    {"Name": "Nigel Hayes-Davis", "GP": 39, "FTM": 128, "FTA": 140, "2PM": 124, "2PA": 249, "3PM": 89, "3PA": 222, "OR": 54, "DR": 152, "AST": 66, "STL": 42, "BLK": 11, "TOV": 54, "PF": 156},
    {"Name": "Jaylen Hoard", "GP": 24, "FTM": 76, "FTA": 96, "2PM": 122, "2PA": 196, "3PM": 12, "3PA": 33, "OR": 31, "DR": 91, "AST": 33, "STL": 31, "BLK": 4, "TOV": 21, "PF": 72},
    {"Name": "Facundo Campazzo", "GP": 39, "FTM": 136, "FTA": 156, "2PM": 89, "2PA": 156, "3PM": 50, "3PA": 152, "OR": 27, "DR": 93, "AST": 234, "STL": 39, "BLK": 3, "TOV": 85, "PF": 156},
    {"Name": "Tornike Shengelia", "GP": 28, "FTM": 117, "FTA": 142, "2PM": 123, "2PA": 240, "3PM": 25, "3PA": 70, "OR": 44, "DR": 95, "AST": 75, "STL": 19, "BLK": 11, "TOV": 70, "PF": 112},
    {"Name": "Mike James", "GP": 41, "FTM": 155, "FTA": 200, "2PM": 135, "2PA": 299, "3PM": 77, "3PA": 229, "OR": 12, "DR": 106, "AST": 237, "STL": 45, "BLK": 0, "TOV": 77, "PF": 164},
    {"Name": "Carlik Jones", "GP": 34, "FTM": 105, "FTA": 122, "2PM": 142, "2PA": 282, "3PM": 30, "3PA": 95, "OR": 17, "DR": 91, "AST": 183, "STL": 34, "BLK": 3, "TOV": 61, "PF": 136},
    {"Name": "CarsEN Edwards", "GP": 35, "FTM": 112, "FTA": 122, "2PM": 150, "2PA": 280, "3PM": 101, "3PA": 280, "OR": 17, "DR": 63, "AST": 115, "STL": 35, "BLK": 3, "TOV": 80, "PF": 140},
    {"Name": "Kevin Punter", "GP": 37, "FTM": 133, "FTA": 144, "2PM": 122, "2PA": 229, "3PM": 77, "3PA": 203, "OR": 11, "DR": 70, "AST": 111, "STL": 48, "BLK": 0, "TOV": 59, "PF": 148},
    {"Name": "Devin Booker", "GP": 28, "FTM": 81, "FTA": 98, "2PM": 120, "2PA": 207, "3PM": 30, "3PA": 78, "OR": 50, "DR": 81, "AST": 44, "STL": 19, "BLK": 5, "TOV": 44, "PF": 109},
    {"Name": "Tyrique Jones", "GP": 32, "FTM": 92, "FTA": 140, "2PM": 137, "2PA": 220, "3PM": 0, "3PA": 0, "OR": 89, "DR": 102, "AST": 32, "STL": 35, "BLK": 22, "TOV": 54, "PF": 128},
    {"Name": "Rokas Jokubaitis", "GP": 28, "FTM": 58, "FTA": 70, "2PM": 112, "2PA": 184, "3PM": 22, "3PA": 61, "OR": 22, "DR": 67, "AST": 128, "STL": 28, "BLK": 0, "TOV": 72, "PF": 86},
    {"Name": "Sylven Francisco", "GP": 34, "FTM": 129, "FTA": 173, "2PM": 71, "2PA": 146, "3PM": 74, "3PA": 217, "OR": 17, "DR": 71, "AST": 153, "STL": 30, "BLK": 13, "TOV": 98, "PF": 136},
    {"Name": "Shane Larkin", "GP": 28, "FTM": 53, "FTA": 61, "2PM": 53, "2PA": 109, "3PM": 56, "3PA": 145, "OR": 11, "DR": 61, "AST": 126, "STL": 33, "BLK": 0, "TOV": 50, "PF": 109},
    {"Name": "Will Clyburn", "GP": 24, "FTM": 48, "FTA": 60, "2PM": 76, "2PA": 146, "3PM": 43, "3PA": 124, "OR": 24, "DR": 88, "AST": 57, "STL": 26, "BLK": 4, "TOV": 33, "PF": 79},
    {"Name": "Juancho Hernangomez", "GP": 40, "FTM": 40, "FTA": 64, "2PM": 88, "2PA": 152, "3PM": 60, "3PA": 144, "OR": 64, "DR": 216, "AST": 56, "STL": 36, "BLK": 12, "TOV": 24, "PF": 80},
    {"Name": "Walter Tavares", "GP": 40, "FTM": 72, "FTA": 96, "2PM": 168, "2PA": 228, "3PM": 0, "3PA": 0, "OR": 96, "DR": 164, "AST": 48, "STL": 28, "BLK": 48, "TOV": 80, "PF": 112},
    {"Name": "Filip Petrusev", "GP": 32, "FTM": 102, "FTA": 153, "2PM": 134, "2PA": 214, "3PM": 16, "3PA": 57, "OR": 54, "DR": 92, "AST": 51, "STL": 22, "BLK": 16, "TOV": 38, "PF": 121},
    {"Name": "Elijah Bryant", "GP": 38, "FTM": 98, "FTA": 110, "2PM": 129, "2PA": 262, "3PM": 57, "3PA": 155, "OR": 22, "DR": 136, "AST": 117, "STL": 45, "BLK": 7, "TOV": 83, "PF": 140},
    {"Name": "Nikola Milutinov", "GP": 29, "FTM": 66, "FTA": 81, "2PM": 84, "2PA": 145, "3PM": 0, "3PA": 0, "OR": 78, "DR": 89, "AST": 23, "STL": 17, "BLK": 20, "TOV": 17, "PF": 72},
    {"Name": "Donta Hall", "GP": 34, "FTM": 68, "FTA": 98, "2PM": 115, "2PA": 159, "3PM": 0, "3PA": 0, "OR": 64, "DR": 119, "AST": 30, "STL": 17, "BLK": 37, "TOV": 23, "PF": 88},
    {"Name": "Mario Hezonja", "GP": 38, "FTM": 68, "FTA": 83, "2PM": 140, "2PA": 224, "3PM": 72, "3PA": 231, "OR": 19, "DR": 182, "AST": 57, "STL": 30, "BLK": 3, "TOV": 60, "PF": 79},
    {"Name": "Isaia Cordinier", "GP": 34, "FTM": 91, "FTA": 115, "2PM": 115, "2PA": 207, "3PM": 27, "3PA": 102, "OR": 34, "DR": 98, "AST": 132, "STL": 23, "BLK": 10, "TOV": 68, "PF": 112},
    {"Name": "Vincent Poirier", "GP": 39, "FTM": 74, "FTA": 109, "2PM": 148, "2PA": 222, "3PM": 0, "3PA": 3, "OR": 78, "DR": 117, "AST": 46, "STL": 23, "BLK": 50, "TOV": 35, "PF": 85},
    {"Name": "Elie Okobo", "GP": 35, "FTM": 101, "FTA": 115, "2PM": 105, "2PA": 210, "3PM": 42, "3PA": 108, "OR": 3, "DR": 59, "AST": 143, "STL": 38, "BLK": 7, "TOV": 63, "PF": 108},
    {"Name": "Shavon Shields", "GP": 28, "FTM": 56, "FTA": 78, "2PM": 75, "2PA": 140, "3PM": 42, "3PA": 100, "OR": 16, "DR": 84, "AST": 72, "STL": 19, "BLK": 0, "TOV": 42, "PF": 78},
    {"Name": "Nando De Colo", "GP": 32, "FTM": 89, "FTA": 96, "2PM": 57, "2PA": 105, "3PM": 54, "3PA": 144, "OR": 9, "DR": 44, "AST": 144, "STL": 25, "BLK": 0, "TOV": 73, "PF": 108},
    {"Name": "Nick Weiler-Babb", "GP": 34, "FTM": 23, "FTA": 34, "2PM": 37, "2PA": 68, "3PM": 61, "3PA": 139, "OR": 44, "DR": 98, "AST": 166, "STL": 51, "BLK": 3, "TOV": 54, "PF": 54},
    {"Name": "Evan Fournier", "GP": 37, "FTM": 107, "FTA": 148, "2PM": 107, "2PA": 210, "3PM": 92, "3PA": 255, "OR": 22, "DR": 59, "AST": 96, "STL": 40, "BLK": 3, "TOV": 66, "PF": 111},
    {"Name": "Dzanan Musa", "GP": 35, "FTM": 112, "FTA": 136, "2PM": 91, "2PA": 168, "3PM": 45, "3PA": 122, "OR": 17, "DR": 84, "AST": 70, "STL": 14, "BLK": 3, "TOV": 59, "PF": 112},
    {"Name": "Jabari Parker", "GP": 39, "FTM": 50, "FTA": 62, "2PM": 132, "2PA": 237, "3PM": 74, "3PA": 195, "OR": 39, "DR": 117, "AST": 66, "STL": 31, "BLK": 7, "TOV": 58, "PF": 66},
    {"Name": "Neal Sako", "GP": 33, "FTM": 46, "FTA": 79, "2PM": 125, "2PA": 184, "3PM": 0, "3PA": 0, "OR": 89, "DR": 112, "AST": 26, "STL": 26, "BLK": 16, "TOV": 29, "PF": 69},
    {"Name": "Alpha Diallo", "GP": 35, "FTM": 45, "FTA": 70, "2PM": 129, "2PA": 213, "3PM": 31, "3PA": 73, "OR": 52, "DR": 87, "AST": 59, "STL": 35, "BLK": 10, "TOV": 42, "PF": 87},
    {"Name": "Kostas Sloukas", "GP": 39, "FTM": 113, "FTA": 120, "2PM": 42, "2PA": 97, "3PM": 50, "3PA": 140, "OR": 15, "DR": 62, "AST": 187, "STL": 31, "BLK": 3, "TOV": 62, "PF": 109},
    {"Name": "Levi Randolph", "GP": 33, "FTM": 85, "FTA": 92, "2PM": 105, "2PA": 221, "3PM": 33, "3PA": 82, "OR": 39, "DR": 85, "AST": 59, "STL": 19, "BLK": 0, "TOV": 39, "PF": 95},
    {"Name": "Roman Sorkin", "GP": 33, "FTM": 72, "FTA": 85, "2PM": 132, "2PA": 227, "3PM": 29, "3PA": 92, "OR": 56, "DR": 79, "AST": 36, "STL": 16, "BLK": 16, "TOV": 49, "PF": 75},
    {"Name": "Marko Guduric", "GP": 36, "FTM": 90, "FTA": 104, "2PM": 79, "2PA": 133, "3PM": 46, "3PA": 126, "OR": 14, "DR": 79, "AST": 111, "STL": 25, "BLK": 3, "TOV": 72, "PF": 115},
    {"Name": "Chimezie Metu", "GP": 24, "FTM": 26, "FTA": 36, "2PM": 88, "2PA": 141, "3PM": 19, "3PA": 55, "OR": 24, "DR": 91, "AST": 24, "STL": 14, "BLK": 14, "TOV": 40, "PF": 43},
    {"Name": "Darius Thompson", "GP": 39, "FTM": 42, "FTA": 54, "2PM": 74, "2PA": 132, "3PM": 58, "3PA": 136, "OR": 23, "DR": 54, "AST": 175, "STL": 35, "BLK": 15, "TOV": 46, "PF": 58},
    {"Name": "Tamir Blatt", "GP": 26, "FTM": 39, "FTA": 39, "2PM": 18, "2PA": 36, "3PM": 52, "3PA": 148, "OR": 10, "DR": 52, "AST": 174, "STL": 13, "BLK": 0, "TOV": 75, "PF": 54},
    {"Name": "Trent Forrest", "GP": 34, "FTM": 54, "FTA": 64, "2PM": 108, "2PA": 207, "3PM": 20, "3PA": 57, "OR": 13, "DR": 81, "AST": 159, "STL": 27, "BLK": 6, "TOV": 64, "PF": 74},
    {"Name": "Jan Vesely", "GP": 24, "FTM": 36, "FTA": 45, "2PM": 79, "2PA": 144, "3PM": 7, "3PA": 14, "OR": 26, "DR": 60, "AST": 45, "STL": 26, "BLK": 12, "TOV": 21, "PF": 52},
    {"Name": "Shabazz Napier", "GP": 33, "FTM": 82, "FTA": 89, "2PM": 49, "2PA": 89, "3PM": 52, "3PA": 128, "OR": 16, "DR": 59, "AST": 105, "STL": 36, "BLK": 0, "TOV": 62, "PF": 82},
    {"Name": "Nikola Kalinic", "GP": 35, "FTM": 52, "FTA": 80, "2PM": 70, "2PA": 122, "3PM": 38, "3PA": 91, "OR": 45, "DR": 101, "AST": 91, "STL": 28, "BLK": 3, "TOV": 59, "PF": 94},
    {"Name": "Tadas Sedekerskis", "GP": 25, "FTM": 25, "FTA": 35, "2PM": 50, "2PA": 80, "3PM": 20, "3PA": 45, "OR": 35, "DR": 85, "AST": 42, "STL": 7, "BLK": 5, "TOV": 20, "PF": 47},
    {"Name": "Sterling Brown", "GP": 34, "FTM": 37, "FTA": 40, "2PM": 88, "2PA": 153, "3PM": 68, "3PA": 146, "OR": 23, "DR": 81, "AST": 71, "STL": 27, "BLK": 6, "TOV": 47, "PF": 44},
    {"Name": "Yanni Wetzell", "GP": 28, "FTM": 47, "FTA": 72, "2PM": 117, "2PA": 207, "3PM": 11, "3PA": 28, "OR": 44, "DR": 78, "AST": 44, "STL": 22, "BLK": 5, "TOV": 42, "PF": 84},
    {"Name": "Tre'shawn Ward", "GP": 38, "FTM": 60, "FTA": 79, "2PM": 83, "2PA": 140, "3PM": 64, "3PA": 193, "OR": 41, "DR": 148, "AST": 49, "STL": 34, "BLK": 7, "TOV": 98, "PF": 87},
    {"Name": "Daniel Oturu", "GP": 38, "FTM": 60, "FTA": 87, "2PM": 136, "2PA": 190, "3PM": 0, "3PA": 0, "OR": 76, "DR": 83, "AST": 19, "STL": 19, "BLK": 38, "TOV": 41, "PF": 83},
    {"Name": "Wade Baldwin IV", "GP": 27, "FTM": 62, "FTA": 78, "2PM": 81, "2PA": 170, "3PM": 24, "3PA": 81, "OR": 16, "DR": 54, "AST": 99, "STL": 24, "BLK": 2, "TOV": 56, "PF": 81},
    {"Name": "Treveon Williams", "GP": 32, "FTM": 41, "FTA": 64, "2PM": 112, "2PA": 204, "3PM": 16, "3PA": 60, "OR": 67, "DR": 140, "AST": 76, "STL": 19, "BLK": 16, "TOV": 89, "PF": 54},
    {"Name": "Willy Hernangomez", "GP": 34, "FTM": 64, "FTA": 98, "2PM": 105, "2PA": 166, "3PM": 0, "3PA": 0, "OR": 57, "DR": 81, "AST": 17, "STL": 20, "BLK": 3, "TOV": 37, "PF": 105},
    {"Name": "Brandon Davies", "GP": 33, "FTM": 46, "FTA": 79, "2PM": 92, "2PA": 178, "3PM": 33, "3PA": 66, "OR": 29, "DR": 89, "AST": 49, "STL": 29, "BLK": 13, "TOV": 46, "PF": 105},
    {"Name": "Martin Hermannsson", "GP": 24, "FTM": 48, "FTA": 57, "2PM": 64, "2PA": 127, "3PM": 19, "3PA": 62, "OR": 9, "DR": 28, "AST": 136, "STL": 14, "BLK": 0, "TOV": 28, "PF": 57},
    {"Name": "Jerian Grant", "GP": 41, "FTM": 61, "FTA": 73, "2PM": 73, "2PA": 131, "3PM": 49, "3PA": 114, "OR": 16, "DR": 73, "AST": 131, "STL": 36, "BLK": 4, "TOV": 32, "PF": 90},
    {"Name": "Nadir Hifi", "GP": 38, "FTM": 102, "FTA": 117, "2PM": 91, "2PA": 186, "3PM": 95, "3PA": 281, "OR": 19, "DR": 60, "AST": 49, "STL": 22, "BLK": 0, "TOV": 57, "PF": 110},
    {"Name": "Andre Roberson", "GP": 25, "FTM": 25, "FTA": 40, "2PM": 55, "2PA": 105, "3PM": 25, "3PA": 70, "OR": 45, "DR": 110, "AST": 35, "STL": 30, "BLK": 27, "TOV": 65, "PF": 30},
    {"Name": "Codi Miller-McIntyre", "GP": 35, "FTM": 31, "FTA": 42, "2PM": 105, "2PA": 203, "3PM": 38, "3PA": 129, "OR": 21, "DR": 87, "AST": 161, "STL": 21, "BLK": 0, "TOV": 80, "PF": 63},
    {"Name": "Fabien Causeur", "GP": 22, "FTM": 30, "FTA": 39, "2PM": 33, "2PA": 57, "3PM": 28, "3PA": 52, "OR": 13, "DR": 46, "AST": 37, "STL": 22, "BLK": 2, "TOV": 19, "PF": 35},
    {"Name": "Isaac Bonga", "GP": 30, "FTM": 42, "FTA": 45, "2PM": 30, "2PA": 63, "3PM": 42, "3PA": 102, "OR": 45, "DR": 87, "AST": 33, "STL": 21, "BLK": 15, "TOV": 21, "PF": 42},
    {"Name": "Tomas Satoransky", "GP": 39, "FTM": 27, "FTA": 39, "2PM": 66, "2PA": 128, "3PM": 23, "3PA": 70, "OR": 31, "DR": 93, "AST": 206, "STL": 35, "BLK": 3, "TOV": 70, "PF": 62},
    {"Name": "Nikos Rogkavopoulos", "GP": 33, "FTM": 29, "FTA": 36, "2PM": 49, "2PA": 92, "3PM": 62, "3PA": 148, "OR": 39, "DR": 89, "AST": 33, "STL": 16, "BLK": 3, "TOV": 16, "PF": 29},
    {"Name": "David McCormack", "GP": 28, "FTM": 50, "FTA": 70, "2PM": 92, "2PA": 154, "3PM": 0, "3PA": 2, "OR": 44, "DR": 84, "AST": 16, "STL": 22, "BLK": 2, "TOV": 44, "PF": 70},
    {"Name": "Mikael Jantunen", "GP": 38, "FTM": 26, "FTA": 34, "2PM": 41, "2PA": 68, "3PM": 57, "3PA": 148, "OR": 60, "DR": 121, "AST": 38, "STL": 26, "BLK": 7, "TOV": 15, "PF": 60},
    {"Name": "Ante Zizic", "GP": 25, "FTM": 30, "FTA": 45, "2PM": 85, "2PA": 135, "3PM": 0, "3PA": 0, "OR": 47, "DR": 47, "AST": 7, "STL": 7, "BLK": 15, "TOV": 32, "PF": 40},
    {"Name": "Omer Yurtseven", "GP": 31, "FTM": 34, "FTA": 46, "2PM": 108, "2PA": 170, "3PM": 3, "3PA": 9, "OR": 55, "DR": 68, "AST": 18, "STL": 12, "BLK": 21, "TOV": 43, "PF": 43},
    {"Name": "Johannes Voigtmann", "GP": 36, "FTM": 21, "FTA": 32, "2PM": 50, "2PA": 82, "3PM": 39, "3PA": 108, "OR": 43, "DR": 136, "AST": 86, "STL": 18, "BLK": 7, "TOV": 54, "PF": 39},
    {"Name": "Jaleel Blossomgame", "GP": 40, "FTM": 36, "FTA": 56, "2PM": 100, "2PA": 164, "3PM": 24, "3PA": 76, "OR": 52, "DR": 112, "AST": 20, "STL": 16, "BLK": 8, "TOV": 16, "PF": 88},
    {"Name": "Mam Jaiteh", "GP": 31, "FTM": 37, "FTA": 55, "2PM": 99, "2PA": 151, "3PM": 0, "3PA": 0, "OR": 46, "DR": 74, "AST": 18, "STL": 15, "BLK": 9, "TOV": 34, "PF": 62},
    {"Name": "Alec Peters", "GP": 40, "FTM": 60, "FTA": 64, "2PM": 64, "2PA": 112, "3PM": 48, "3PA": 88, "OR": 40, "DR": 68, "AST": 32, "STL": 12, "BLK": 0, "TOV": 16, "PF": 72},
    {"Name": "Kaleb Hayes", "GP": 38, "FTM": 53, "FTA": 68, "2PM": 95, "2PA": 155, "3PM": 0, "3PA": 0, "OR": 68, "DR": 106, "AST": 19, "STL": 38, "BLK": 30, "TOV": 34, "PF": 60},
    {"Name": "Jordan Loyd", "GP": 35, "FTM": 70, "FTA": 77, "2PM": 63, "2PA": 119, "3PM": 45, "3PA": 122, "OR": 21, "DR": 80, "AST": 59, "STL": 21, "BLK": 3, "TOV": 38, "PF": 80},
    {"Name": "Matteo Spagnolo", "GP": 27, "FTM": 51, "FTA": 64, "2PM": 86, "2PA": 191, "3PM": 10, "3PA": 45, "OR": 13, "DR": 40, "AST": 102, "STL": 13, "BLK": 0, "TOV": 40, "PF": 72},
    {"Name": "Leandro Bolmaro", "GP": 25, "FTM": 30, "FTA": 45, "2PM": 60, "2PA": 115, "3PM": 7, "3PA": 35, "OR": 10, "DR": 47, "AST": 77, "STL": 27, "BLK": 5, "TOV": 47, "PF": 62},
    {"Name": "Georgios Papagiannis", "GP": 29, "FTM": 17, "FTA": 19, "2PM": 81, "2PA": 118, "3PM": 11, "3PA": 29, "OR": 31, "DR": 66, "AST": 14, "STL": 14, "BLK": 37, "TOV": 6, "PF": 66},
    {"Name": "Donta Hall", "GP": 32, "FTM": 38, "FTA": 44, "2PM": 51, "2PA": 96, "3PM": 35, "3PA": 92, "OR": 22, "DR": 48, "AST": 108, "STL": 16, "BLK": 3, "TOV": 22, "PF": 57},
    {"Name": "Gabriel Deck", "GP": 28, "FTM": 33, "FTA": 53, "2PM": 61, "2PA": 100, "3PM": 22, "3PA": 50, "OR": 28, "DR": 61, "AST": 39, "STL": 14, "BLK": 5, "TOV": 28, "PF": 50},
    {"Name": "Nigel Williams-Goss", "GP": 35, "FTM": 77, "FTA": 94, "2PM": 73, "2PA": 157, "3PM": 24, "3PA": 70, "OR": 7, "DR": 66, "AST": 119, "STL": 24, "BLK": 3, "TOV": 80, "PF": 80},
    {"Name": "Cedi Osman", "GP": 39, "FTM": 89, "FTA": 113, "2PM": 62, "2PA": 117, "3PM": 50, "3PA": 136, "OR": 19, "DR": 85, "AST": 27, "STL": 19, "BLK": 7, "TOV": 15, "PF": 85},
    {"Name": "Justin Anderson", "GP": 37, "FTM": 37, "FTA": 41, "2PM": 66, "2PA": 107, "3PM": 29, "3PA": 74, "OR": 25, "DR": 77, "AST": 51, "STL": 25, "BLK": 11, "TOV": 25, "PF": 66},
    {"Name": "Dario Brizuela", "GP": 36, "FTM": 39, "FTA": 50, "2PM": 64, "2PA": 122, "3PM": 64, "3PA": 140, "OR": 10, "DR": 39, "AST": 79, "STL": 14, "BLK": 3, "TOV": 46, "PF": 72},
    {"Name": "Tarik Biberovic", "GP": 37, "FTM": 29, "FTA": 37, "2PM": 55, "2PA": 111, "3PM": 81, "3PA": 185, "OR": 33, "DR": 81, "AST": 51, "STL": 18, "BLK": 7, "TOV": 18, "PF": 85},
    {"Name": "Moustapha Fall", "GP": 35, "FTM": 28, "FTA": 66, "2PM": 87, "2PA": 119, "3PM": 0, "3PA": 0, "OR": 45, "DR": 101, "AST": 66, "STL": 10, "BLK": 28, "TOV": 10, "PF": 84},
    {"Name": "Nemanja Nedovic", "GP": 27, "FTM": 37, "FTA": 48, "2PM": 37, "2PA": 78, "3PM": 45, "3PA": 116, "OR": 13, "DR": 27, "AST": 78, "STL": 13, "BLK": 2, "TOV": 35, "PF": 51},
    {"Name": "Edgaras Ulanovas", "GP": 34, "FTM": 68, "FTA": 81, "2PM": 37, "2PA": 78, "3PM": 27, "3PA": 64, "OR": 34, "DR": 61, "AST": 61, "STL": 17, "BLK": 3, "TOV": 30, "PF": 91},
    {"Name": "Rodrigue Beaubois", "GP": 33, "FTM": 19, "FTA": 23, "2PM": 52, "2PA": 92, "3PM": 56, "3PA": 122, "OR": 6, "DR": 39, "AST": 52, "STL": 23, "BLK": 9, "TOV": 33, "PF": 62},
    {"Name": "Matthew Strazel", "GP": 41, "FTM": 69, "FTA": 82, "2PM": 49, "2PA": 98, "3PM": 57, "3PA": 139, "OR": 20, "DR": 32, "AST": 98, "STL": 20, "BLK": 0, "TOV": 41, "PF": 82},
    {"Name": "Maodo Lo", "GP": 29, "FTM": 29, "FTA": 34, "2PM": 72, "2PA": 127, "3PM": 37, "3PA": 116, "OR": 11, "DR": 31, "AST": 60, "STL": 11, "BLK": 0, "TOV": 31, "PF": 46},
    {"Name": "Mohamed Diouf", "GP": 31, "FTM": 62, "FTA": 86, "2PM": 65, "2PA": 108, "3PM": 0, "3PA": 0, "OR": 40, "DR": 55, "AST": 12, "STL": 18, "BLK": 12, "TOV": 18, "PF": 62},
    {"Name": "Nico Mannion", "GP": 27, "FTM": 40, "FTA": 51, "2PM": 51, "2PA": 89, "3PM": 29, "3PA": 89, "OR": 2, "DR": 35, "AST": 108, "STL": 18, "BLK": 0, "TOV": 62, "PF": 67},
    {"Name": "Alex Smailagic", "GP": 29, "FTM": 34, "FTA": 49, "2PM": 66, "2PA": 98, "3PM": 23, "3PA": 63, "OR": 31, "DR": 52, "AST": 11, "STL": 11, "BLK": 17, "TOV": 52, "PF": 66},
    {"Name": "Gabriel Procida", "GP": 26, "FTM": 44, "FTA": 57, "2PM": 72, "2PA": 117, "3PM": 20, "3PA": 96, "OR": 15, "DR": 44, "AST": 20, "STL": 18, "BLK": 7, "TOV": 31, "PF": 52},
    {"Name": "Matthew Morgan", "GP": 34, "FTM": 74, "FTA": 81, "2PM": 40, "2PA": 74, "3PM": 37, "3PA": 132, "OR": 6, "DR": 51, "AST": 88, "STL": 17, "BLK": 0, "TOV": 34, "PF": 78},
    {"Name": "Lorenzo Brown", "GP": 38, "FTM": 34, "FTA": 41, "2PM": 60, "2PA": 117, "3PM": 26, "3PA": 79, "OR": 11, "DR": 64, "AST": 102, "STL": 30, "BLK": 3, "TOV": 41, "PF": 49}
]
    
    selected = random.sample(all_100, min(len(all_100), 25))
    
    formatted = []
    for p in selected:
        formatted.append({
            "Name": p["Name"],
            "FT_Made": p["FTM"], "FT_Attempted": p["FTA"],
            "Two_Made": p["2PM"], "Two_Attempted": p["2PA"],
            "Three_Made": p["3PM"], "Three_Attempted": p["3PA"],
            "Off_Rebounds": p["OR"], "Def_Rebounds": p["DR"],
            "Assists": p["AST"], "Steals": p["STL"], "Blocks": p["BLK"],
            "Turnovers": p["TOV"], "Fouls": p["PF"], "Matches": p["GP"]
        })
    return formatted

def main():
    print("    BASKETBALL DATA CENTRAL (Randomizer) ")
    
    #Check if streamlit send a number
    if len(sys.argv) > 1:
        choice = sys.argv[1]
    else:
        print("1. NBA Only (Top 50)")
        print("2. Euroleague Only (Random 25)")
        print("3. Mixed (25 NBA + 25 Random Euroleague)")
        choice = input("\n Select mode (1-3): ")
    
    final_players = []
    if choice == '1':
        final_players = get_nba_data(50)
    elif choice == '2':
        final_players = get_euroleague_random_25()
    elif choice == '3':
        final_players = get_nba_data(25) + get_euroleague_random_25()
    else:
        print(" Invalid selection.")
        return

    output = {"players": final_players}
    
    filename = "../tests/nba.json" 
    
    with open(filename, "w", encoding="utf-8") as f:
        json.dump(output, f, indent=4, ensure_ascii=False)

    print(f"\n Success! {len(final_players)} players saved to '{filename}'")

if __name__ == "__main__":
    main()