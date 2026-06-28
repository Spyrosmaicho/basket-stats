"""
Player image resolution (PRO SYSTEM):
  1. Local cache  (assets/cache/<slug>.png)
  2. NBA CDN      (via nba_api EXACT match)
  3. Wikipedia    (global / EuroLeague - Single Request Action API)
  4. UI-Avatars   (fallback to Player Initials if everything fails)
"""

import os
import re
import requests
import urllib.parse
import unicodedata
import streamlit as st
from config import ASSETS_DIR
import time
from requests.adapters import HTTPAdapter
from requests.packages.urllib3.util.retry import Retry

CACHE_DIR = os.path.join(ASSETS_DIR, "cache")
os.makedirs(CACHE_DIR, exist_ok=True)

HEADERS = {
    "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/120.0.0.0 Safari/537.36",
    "Accept": "text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8"
}

# ─────────────────────────────────────────────
# UTIL
# ─────────────────────────────────────────────
def _normalize_name(name: str) -> str:
    if not name:
        return ""
    nfkd_form = unicodedata.normalize('NFKD', name)
    normalized = ''.join([c for c in nfkd_form if not unicodedata.combining(c)])
    return normalized.lower().strip()

def _slug(name: str) -> str:
    return re.sub(r"[^a-z0-9_]", "_", _normalize_name(name))

def _file_to_data_uri(path: str) -> str:
    import base64
    with open(path, "rb") as f:
        b64 = base64.b64encode(f.read()).decode()
    return f"data:image/png;base64,{b64}"

def _generate_initials_avatar(name: str) -> str:
    encoded_name = urllib.parse.quote(name)
    return f"https://ui-avatars.com/api/?name={encoded_name}&background=1E293B&color=fff&size=200&font-size=0.4"

# ─────────────────────────────────────────────
# NBA ID MAP
# ─────────────────────────────────────────────
@st.cache_data(show_spinner=False)
def _build_nba_id_map() -> dict:
    try:
        from nba_api.stats.static import players as nba_players
        mapping = {}
        for p in nba_players.get_players():
            full = _normalize_name(p["full_name"])
            mapping[full] = p["id"]
            
            last = full.split()[-1]
            if last not in mapping:
                mapping[last] = p["id"]
                
        return mapping
    except Exception:
        return {}

def _resolve_nba_id(name: str):
    id_map = _build_nba_id_map()
    if not id_map:
        return None
    key = _normalize_name(name)
    
    if key in id_map:
        return id_map[key]
        
    last = key.split()[-1] if key.split() else ""
    if last in id_map:
        return id_map[last]
        
    return None

session = requests.Session()
retry = Retry(total=3, backoff_factor=0.5, status_forcelist=[429, 500, 502, 503, 504])
adapter = HTTPAdapter(max_retries=retry)
session.mount('http://', adapter)
session.mount('https://', adapter)

# ─────────────────────────────────────────────
# WIKIPEDIA IMAGE PROVIDER 
# ─────────────────────────────────────────────
def _wikimedia_image_download(name: str, local_path: str) -> bool:
    try:
        time.sleep(0.2) 
        
        search_term = urllib.parse.quote(f"{name} basketball")
        url = f"https://en.wikipedia.org/w/api.php?action=query&generator=search&gsrsearch={search_term}&gsrlimit=1&prop=pageimages&piprop=thumbnail&pithumbsize=300&format=json"

        r = session.get(url, headers=HEADERS, timeout=5)
        if r.status_code != 200:
            return False

        pages = r.json().get("query", {}).get("pages", {})
        
        if not pages:
            time.sleep(0.2) 
            search_term_fb = urllib.parse.quote(name)
            url_fb = f"https://en.wikipedia.org/w/api.php?action=query&generator=search&gsrsearch={search_term_fb}&gsrlimit=1&prop=pageimages&piprop=thumbnail&pithumbsize=300&format=json"
            r_fb = session.get(url_fb, headers=HEADERS, timeout=5)
            pages = r_fb.json().get("query", {}).get("pages", {})

        for page_id, page_data in pages.items():
            thumb_url = page_data.get("thumbnail", {}).get("source")
            if thumb_url:
                img_data = session.get(thumb_url, headers=HEADERS, timeout=5)
                if img_data.status_code == 200:
                    with open(local_path, "wb") as f:
                        f.write(img_data.content)
                    return True
        return False
    except Exception:
        return False

# ─────────────────────────────────────────────
# MAIN RESOLVER
# ─────────────────────────────────────────────
def get_player_image_url(name: str) -> str:
    if not name:
        return _generate_initials_avatar("Unknown")

    slug = _slug(name)
    local_path = os.path.join(CACHE_DIR, f"{slug}.png")

    # 1. LOCAL CACHE
    if os.path.exists(local_path):
        return _file_to_data_uri(local_path)

    # 2. NBA CDN
    player_id = _resolve_nba_id(name)
    if player_id:
        url = f"https://cdn.nba.com/headshots/nba/latest/260x190/{player_id}.png"
        try:
            r = requests.get(url, headers=HEADERS, timeout=5)
            if r.status_code == 200:
                with open(local_path, "wb") as f:
                    f.write(r.content)
                return _file_to_data_uri(local_path)
        except Exception:
            pass

    # 3. WIKIPEDIA
    if _wikimedia_image_download(name, local_path):
        return _file_to_data_uri(local_path)

    # 4. FALLBACK (Initials Avatar)
    return _generate_initials_avatar(name)