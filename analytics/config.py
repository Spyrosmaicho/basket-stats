import os

# ==========================================
# PATHS
# ==========================================

BASE_DIR = os.path.dirname(os.path.abspath(__file__))
RUN_DIR  = os.path.abspath(os.path.join(BASE_DIR, "../run"))
DB_PATH  = os.path.abspath(os.path.join(BASE_DIR, "../database/nba_stats.db"))
TESTS_DIR = os.path.abspath(os.path.join(BASE_DIR, "../tests"))
ASSETS_DIR = os.path.join(BASE_DIR, "assets")

# ==========================================
# THEME COLORS
# ==========================================

PRIMARY    = "#3B82F6"
SECONDARY  = "#F97316"
SUCCESS    = "#22C55E"
DANGER     = "#EF4444"
WARNING    = "#EAB308"
ACCENT     = "#A855F7"

BACKGROUND = "#0F172A"
CARD       = "#1E293B"
CARD_HOVER = "#243247"
BORDER     = "#334155"
TEXT       = "#F8FAFC"
TEXT_MUTED = "#94A3B8"

GOLD   = "#F59E0B"
SILVER = "#94A3B8"
BRONZE = "#B45309"

# ==========================================
# TEAM COLORS
# ==========================================

TEAM_COLORS = {
    "Lakers":       {"primary": "#552583", "secondary": "#FDB927"},
    "Celtics":      {"primary": "#007A33", "secondary": "#BA9653"},
    "Warriors":     {"primary": "#1D428A", "secondary": "#FFC72C"},
    "Bulls":        {"primary": "#CE1141", "secondary": "#000000"},
    "Heat":         {"primary": "#98002E", "secondary": "#F9A01B"},
    "Nets":         {"primary": "#000000", "secondary": "#FFFFFF"},
    "Knicks":       {"primary": "#006BB6", "secondary": "#F58426"},
    "Bucks":        {"primary": "#00471B", "secondary": "#EEE1C6"},
    "Mavericks":    {"primary": "#00538C", "secondary": "#002B5E"},
    "Suns":         {"primary": "#1D1160", "secondary": "#E56020"},
    "Clippers":     {"primary": "#C8102E", "secondary": "#1D428A"},
    "76ers":        {"primary": "#006BB6", "secondary": "#ED174C"},
    "Raptors":      {"primary": "#CE1141", "secondary": "#000000"},
    "Nuggets":      {"primary": "#0E2240", "secondary": "#FEC524"},
    "Thunder":      {"primary": "#007AC1", "secondary": "#EF3B24"},
    "Grizzlies":    {"primary": "#5D76A9", "secondary": "#12173F"},
    "Spurs":        {"primary": "#C4CED4", "secondary": "#000000"},
    "Pelicans":     {"primary": "#0C2340", "secondary": "#C8102E"},
    "Trail Blazers":{"primary": "#E03A3E", "secondary": "#000000"},
    "Timberwolves": {"primary": "#0C2340", "secondary": "#236192"},
    "Jazz":         {"primary": "#002B5C", "secondary": "#00471B"},
    "Kings":        {"primary": "#5A2D81", "secondary": "#63727A"},
    "Rockets":      {"primary": "#CE1141", "secondary": "#000000"},
    "Pistons":      {"primary": "#C8102E", "secondary": "#1D42BA"},
    "Pacers":       {"primary": "#002D62", "secondary": "#FDBB30"},
    "Cavaliers":    {"primary": "#860038", "secondary": "#FDBB30"},
    "Hawks":        {"primary": "#C1D32F", "secondary": "#E03A3E"},
    "Hornets":      {"primary": "#1D1160", "secondary": "#00788C"},
    "Magic":        {"primary": "#0077C0", "secondary": "#C4CED4"},
    "Wizards":      {"primary": "#002B5C", "secondary": "#E31837"},
}

# ==========================================
# NBA HEADSHOT URL
# ==========================================

NBA_HEADSHOT_URL = "https://cdn.nba.com/headshots/nba/latest/260x190/{player_id}.png"
ANONYMOUS_AVATAR = "https://cdn-icons-png.flaticon.com/512/847/847969.png"
