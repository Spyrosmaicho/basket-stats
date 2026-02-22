import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

try:
    df = pd.read_csv('players.csv')
except FileNotFoundError:
    print("Error! Couldn't find players.csv file!")
    exit()

fig, axs = plt.subplots(2, 2, figsize=(16, 10))
fig.suptitle('Team Performance Analytics Dashboard', fontsize=22, fontweight='bold')

top_scorers = df.sort_values(by='Points', ascending=False).head(5)
x = np.arange(len(top_scorers))
width = 0.25

axs[0, 0].bar(x - width, top_scorers['Points'], width, label='Points', color='#d62728')
axs[0, 0].bar(x, top_scorers['Off_Reb'] + top_scorers['Def_Reb'], width, label='Rebounds', color='#1f77b4')
axs[0, 0].bar(x + width, top_scorers['Assists'], width, label='Assists', color='#2ca02c')

axs[0, 0].set_title('Top 5 Players (Overall Impact)', fontsize=14, fontweight='bold')
axs[0, 0].set_xticks(x)
axs[0, 0].set_xticklabels(top_scorers['Name'])
axs[0, 0].legend()
axs[0, 0].grid(axis='y', linestyle='--', alpha=0.7)

total_1pt = df['1pt_M'].sum() * 1
total_2pt = df['2pt_M'].sum() * 2
total_3pt = df['3pt_M'].sum() * 3

labels = ['Free Throws (1pt)', 'Two Pointers (2pt)', 'Three Pointers (3pt)']
sizes = [total_1pt, total_2pt, total_3pt]
colors = ['#9467bd', '#ff7f0e', '#8c564b']
explode = (0, 0, 0.1) 

axs[0, 1].pie(sizes, explode=explode, labels=labels, colors=colors, autopct='%1.1f%%',
              shadow=True, startangle=140, textprops={'fontsize': 12})
axs[0, 1].set_title('Team Scoring Distribution', fontsize=14, fontweight='bold')

axs[1, 0].scatter(df['Turnovers'], df['Assists'], color='#e377c2', s=100, edgecolor='black', zorder=3)

for i, txt in enumerate(df['Name']):
    axs[1, 0].annotate(txt, (df['Turnovers'].iloc[i] + 0.1, df['Assists'].iloc[i] + 0.1), fontsize=9)

axs[1, 0].set_title('Playmaking Efficiency (Ast vs TOs)', fontsize=14, fontweight='bold')
axs[1, 0].set_xlabel('Turnovers (Bad)')
axs[1, 0].set_ylabel('Assists (Good)')
axs[1, 0].axline((0, 0), slope=1, color='gray', linestyle='--')
axs[1, 0].grid(True, linestyle='--', alpha=0.5)

df['Total_Rebounds'] = df['Off_Reb'] + df['Def_Reb']
top_rebs = df.sort_values(by='Total_Rebounds', ascending=False).head(5)

axs[1, 1].bar(top_rebs['Name'], top_rebs['Def_Reb'], label='Defensive Rebounds', color='#17becf')
axs[1, 1].bar(top_rebs['Name'], top_rebs['Off_Reb'], bottom=top_rebs['Def_Reb'], label='Offensive Rebounds', color='#bcbd22')

axs[1, 1].set_title('Top 5 Rebounders (Offensive vs Defensive)', fontsize=14, fontweight='bold')
axs[1, 1].legend()
axs[1, 1].grid(axis='y', linestyle='--', alpha=0.7)

plt.tight_layout(rect=[0, 0.03, 1, 0.95])
plt.savefig('team_dashboard.png', dpi=300, bbox_inches='tight')
print("Dashboard has been succesfully created in 'team_dashboard.png'!")