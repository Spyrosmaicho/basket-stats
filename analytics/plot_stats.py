import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import warnings
import os

# Suppress warnings for cleaner terminal output
warnings.filterwarnings('ignore')

# Δημιουργία υποφακέλου για τα γραφήματα (αν δεν υπάρχει)
output_dir = 'charts'
os.makedirs(output_dir, exist_ok=True)

# 1. Load the data
try:
    df = pd.read_csv('players.csv')
except FileNotFoundError:
    print("Error! Couldn't find players.csv file in the analytics folder!")
    exit()

print("Starting chart generation...")

# -------------------------------------------------------------------
# CHART 1: Top 5 Players (Overall Impact)
# -------------------------------------------------------------------
plt.figure(figsize=(10, 6))
top_scorers = df.sort_values(by='Points', ascending=False).head(5)
x = np.arange(len(top_scorers))
width = 0.25

plt.bar(x - width, top_scorers['Points'], width, label='Points', color='#d62728')
plt.bar(x, top_scorers['Off_Reb'] + top_scorers['Def_Reb'], width, label='Rebounds', color='#1f77b4')
plt.bar(x + width, top_scorers['Assists'], width, label='Assists', color='#2ca02c')

plt.title('Top 5 Players (Overall Impact)', fontsize=14, fontweight='bold')
plt.xticks(x, top_scorers['Name'])
plt.legend()
plt.grid(axis='y', linestyle='--', alpha=0.7)
plt.tight_layout()
plt.savefig(f'{output_dir}/chart_1_overall_impact.png', dpi=300)
plt.close()

# -------------------------------------------------------------------
# CHART 2: Team Scoring Distribution (Pie Chart)
# -------------------------------------------------------------------
plt.figure(figsize=(8, 8))
total_1pt = df['1pt_M'].sum() * 1
total_2pt = df['2pt_M'].sum() * 2
total_3pt = df['3pt_M'].sum() * 3

labels = ['Free Throws (1pt)', 'Two Pointers (2pt)', 'Three Pointers (3pt)']
sizes = [total_1pt, total_2pt, total_3pt]
colors = ['#9467bd', '#ff7f0e', '#8c564b']
explode = (0, 0, 0.1) 

plt.pie(sizes, explode=explode, labels=labels, colors=colors, autopct='%1.1f%%', shadow=True, startangle=140)
plt.title('Team Scoring Distribution', fontsize=14, fontweight='bold')
plt.tight_layout()
plt.savefig(f'{output_dir}/chart_2_scoring_distribution.png', dpi=300)
plt.close()

# -------------------------------------------------------------------
# CHART 3: Playmaking Efficiency (Ast vs TOs)
# -------------------------------------------------------------------
plt.figure(figsize=(10, 6))
plt.scatter(df['Turnovers'], df['Assists'], color='#e377c2', s=100, edgecolor='black', zorder=3)

for i, txt in enumerate(df['Name']):
    plt.annotate(txt, (df['Turnovers'].iloc[i] + 0.1, df['Assists'].iloc[i] + 0.1), fontsize=9)

plt.title('Playmaking Efficiency (Ast vs TOs)', fontsize=14, fontweight='bold')
plt.xlabel('Turnovers (Bad)')
plt.ylabel('Assists (Good)')
max_val = max(df['Turnovers'].max(), df['Assists'].max())
if pd.notna(max_val) and max_val > 0:
    plt.plot([0, max_val], [0, max_val], color='gray', linestyle='--')
plt.grid(True, linestyle='--', alpha=0.5)
plt.tight_layout()
plt.savefig(f'{output_dir}/chart_3_playmaking_efficiency.png', dpi=300)
plt.close()

# -------------------------------------------------------------------
# CHART 4: Top 5 Rebounders (Offensive vs Defensive)
# -------------------------------------------------------------------
plt.figure(figsize=(10, 6))
df['Total_Rebounds'] = df['Off_Reb'] + df['Def_Reb']
top_rebs = df.sort_values(by='Total_Rebounds', ascending=False).head(5)

plt.bar(top_rebs['Name'], top_rebs['Def_Reb'], label='Defensive Rebounds', color='#17becf')
plt.bar(top_rebs['Name'], top_rebs['Off_Reb'], bottom=top_rebs['Def_Reb'], label='Offensive Rebounds', color='#bcbd22')

plt.title('Top 5 Rebounders (Offensive vs Defensive)', fontsize=14, fontweight='bold')
plt.legend()
plt.grid(axis='y', linestyle='--', alpha=0.7)
plt.tight_layout()
plt.savefig(f'{output_dir}/chart_4_rebounding_breakdown.png', dpi=300)
plt.close()

# -------------------------------------------------------------------
# CHART 5: Defensive Impact (Steals & Blocks)
# -------------------------------------------------------------------
plt.figure(figsize=(10, 6))
df['Defensive_Plays'] = df['Steals'] + df['Blocks']
top_def = df.sort_values(by='Defensive_Plays', ascending=False).head(5)
x_def = np.arange(len(top_def))
width_def = 0.35

plt.bar(x_def - width_def/2, top_def['Steals'], width_def, label='Steals', color='#8c564b')
plt.bar(x_def + width_def/2, top_def['Blocks'], width_def, label='Blocks', color='#7f7f7f')

plt.title('Top 5 Defensive Players (Steals & Blocks)', fontsize=14, fontweight='bold')
plt.xticks(x_def, top_def['Name'])
plt.legend()
plt.grid(axis='y', linestyle='--', alpha=0.7)
plt.tight_layout()
plt.savefig(f'{output_dir}/chart_5_defensive_impact.png', dpi=300)
plt.close()

# -------------------------------------------------------------------
# CHART 6: Player Profiles (Radar Chart for Top 2 Scorers)
# -------------------------------------------------------------------
top2 = df.sort_values(by='Points', ascending=False).head(2)

categories = ['Points', 'Rebounds', 'Assists', 'Steals', 'Blocks']
N = len(categories)
angles = [n / float(N) * 2 * np.pi for n in range(N)]
angles += angles[:1] 

fig, ax = plt.subplots(figsize=(8, 8), subplot_kw=dict(polar=True))

colors = ['#1f77b4', '#d62728']
for i, (index, row) in enumerate(top2.iterrows()):
    values = [row['Points'], row['Total_Rebounds'], row['Assists'], row['Steals'], row['Blocks']]
    values += values[:1] 
    ax.plot(angles, values, color=colors[i], linewidth=2, linestyle='solid', label=row['Name'])
    ax.fill(angles, values, color=colors[i], alpha=0.25)

plt.xticks(angles[:-1], categories, size=12, fontweight='bold')
ax.set_title("Top 2 Players Comparison (Radar Chart)", size=16, fontweight='bold', pad=20)
plt.legend(loc='upper right', bbox_to_anchor=(1.2, 1.1))
plt.tight_layout()
plt.savefig(f'{output_dir}/chart_6_player_profiles_radar.png', dpi=300)
plt.close()

# -------------------------------------------------------------------
# CHART 7: Shooting Efficiency (Bubble Chart)
# -------------------------------------------------------------------
plt.figure(figsize=(10, 6))

bubble_sizes = df['Points'] * 30 
scatter = plt.scatter(df['2pt %'], df['3pt %'], s=bubble_sizes, c=df['Points'], cmap='viridis', alpha=0.7, edgecolors='black', zorder=3)

for i, txt in enumerate(df['Name']):
    if df['Points'].iloc[i] > 0:
        plt.annotate(txt, (df['2pt %'].iloc[i], df['3pt %'].iloc[i]), fontsize=9, ha='center', va='center')

plt.colorbar(scatter, label='Total Points Scored')
plt.title('Shooting Efficiency (2PT% vs 3PT%)', fontsize=14, fontweight='bold')
plt.xlabel('2-Point Percentage (%)')
plt.ylabel('3-Point Percentage (%)')
plt.grid(True, linestyle='--', alpha=0.5)
plt.tight_layout()
plt.savefig(f'{output_dir}/chart_7_shooting_efficiency_bubble.png', dpi=300)
plt.close()

# -------------------------------------------------------------------
# CHART 8: Volume vs Efficiency (Points & True Shooting Percentage)
# -------------------------------------------------------------------
fig, ax1 = plt.subplots(figsize=(12, 6))

df['FGA'] = df['2pt_A'] + df['3pt_A']
df['TS_Denom'] = 2 * (df['FGA'] + 0.44 * df['1pt_A'])
df['TS_Pct'] = np.where(df['TS_Denom'] > 0, (df['Points'] / df['TS_Denom']) * 100, 0)

top_5_ts = df.sort_values(by='Points', ascending=False).head(5)

ax1.bar(top_5_ts['Name'], top_5_ts['Points'], color='#17becf', alpha=0.7, label='Points (Volume)')
ax1.set_ylabel('Total Points', color='#17becf', fontsize=12, fontweight='bold')
ax1.tick_params(axis='y', labelcolor='#17becf')

ax2 = ax1.twinx()
ax2.plot(top_5_ts['Name'], top_5_ts['TS_Pct'], color='#ff7f0e', marker='o', linewidth=3, markersize=10, label='TS% (Efficiency)')
ax2.set_ylabel('True Shooting %', color='#ff7f0e', fontsize=12, fontweight='bold')
ax2.tick_params(axis='y', labelcolor='#ff7f0e')

plt.title('Scoring Volume vs True Shooting Efficiency', fontsize=15, fontweight='bold')
fig.tight_layout()
plt.savefig(f'{output_dir}/chart_8_true_shooting_efficiency.png', dpi=300)
plt.close()

print(f"Success! 8 advanced analytics charts have been generated in the '{output_dir}' folder.")