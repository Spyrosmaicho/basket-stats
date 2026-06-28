import os
import sys
import time
import subprocess
import streamlit as st
from config import DB_PATH, TESTS_DIR
from engine.daemon import send_command


def show_sidebar(df):
    # ── Logo ────────────────────────────────────
    st.sidebar.markdown(
        '<div class="sidebar-logo"> PRO HOOPS</div>', unsafe_allow_html=True
    )

    # ── Status block ────────────────────────────
    db_exists = os.path.exists(DB_PATH)
    player_count = len(df) if not df.empty else 0
    dot = '<span class="status-dot-green">●</span>' if db_exists else '<span class="status-dot-red">●</span>'
    status_text = "Connected" if db_exists else "No Database"

    st.sidebar.markdown(
        f"""
<div class="sidebar-status">
  <div style="display:flex;align-items:center;gap:6px;color:#F1F5F9;font-weight:600;font-size:0.85rem;">
    {dot} Database {status_text}
  </div>
  <div class="sidebar-stat">Players loaded <span>{player_count}</span></div>
  <div class="sidebar-stat">Engine <span>{'Running' if db_exists else 'Idle'}</span></div>
</div>
""",
        unsafe_allow_html=True,
    )

    st.sidebar.markdown("---")

    # ── STEP 1: Web API Fetch ────────────────────
    with st.sidebar.expander("  Step 1 · Fetch Web Data", expanded=False):
        fetch_mode = st.selectbox(
            "Roster type:",
            ["1. NBA Only", "2. Euroleague Only", "3. Mixed Mode"],
            label_visibility="collapsed",
        )
        mode_map = {"1. NBA Only": "1", "2. Euroleague Only": "2", "3. Mixed Mode": "3"}
        if st.button("⬇  Fetch Roster", use_container_width=True):
            with st.spinner("Downloading from API…"):
                fetch_script = os.path.join(TESTS_DIR, "fetch_nba.py")
                res = subprocess.run(
                    [sys.executable, fetch_script, mode_map[fetch_mode]],
                    capture_output=True, text=True,
                )
                if res.returncode == 0:
                    st.success(" Data fetched!")
                else:
                    st.error(" Error fetching data.")
                    st.code(res.stderr)

    # ── STEP 2: Load Local File ──────────────────
    with st.sidebar.expander("  Step 2 · Load Local File", expanded=True):
        file_type = st.radio(
            "File type:", ["TXT", "JSON", "CSV"], index=1, horizontal=True
        )
        file_type_map = {"TXT": "1", "JSON": "2", "CSV": "3"}
        file_name = st.text_input("Filename (in /tests/):", value="nba.json")
        if st.button("  Load & Sync", use_container_width=True):
            with st.spinner("Processing with C Engine…"):
                absolute_file_path = os.path.join(TESTS_DIR, file_name)
                success, msg = send_command(
                    f"LOAD|{file_type_map[file_type]}|{absolute_file_path}"
                )
                if success:
                    st.success(" Database synced!")
                    st.rerun()
                else:
                    st.error(f" Load Failed: {msg}")

    # ── STEP 3: Manual Operations ────────────────
    with st.sidebar.expander("  Step 3 · Manual Operations"):
        action = st.selectbox("Action:", ["Add Player", "Remove Player", "Add Stats"])

        if action in ["Add Player", "Remove Player"]:
            target_player = st.text_input("Player Name:")
            if st.button(" Execute", use_container_width=True):
                if target_player:
                    with st.spinner("Executing…"):
                        cmd = (
                            f"ADD_PLAYER|{target_player}"
                            if action == "Add Player"
                            else f"REMOVE|{target_player}"
                        )
                        success, msg = send_command(cmd)
                        if success:
                            st.success(f" {action} completed!")
                            time.sleep(1)
                            st.rerun()
                        else:
                            st.error(f" Failed: {msg}")
                else:
                    st.warning("Enter a name first!")

        elif action == "Add Stats":
            stat_map = {
                "1p Made": "1", "1p Attempted": "2",
                "2p Made": "3", "2p Attempted": "4",
                "3p Made": "5", "3p Attempted": "6",
                "Off Rebounds": "7", "Def Rebounds": "8",
                "Assists": "9",  "Steals": "10",
                "Blocks": "11",  "Turnovers": "12",
                "Fouls": "13",   "Matches": "14",
            }
            stat_c = st.selectbox("Stat:", list(stat_map.keys()))
            target_player = st.text_input("Player Name:")
            val = st.number_input("Value:", min_value=1)
            if st.button("  Update", use_container_width=True):
                if target_player:
                    with st.spinner("Updating…"):
                        success, msg = send_command(
                            f"STATS|{target_player}|{stat_map[stat_c]}|{int(val)}"
                        )
                        if success:
                            st.success(" Stats updated!")
                            time.sleep(1)
                            st.rerun()
                        else:
                            st.error(f" Update Failed: {msg}")
                else:
                    st.warning("Enter a name first!")

    # ── STEP 4: Clear Database ───────────────────
    with st.sidebar.expander("  Step 4 · Clear Database"):
        st.warning("This will permanently delete all data.", icon="⚠️")
        if st.button("🗑  Delete All Data", use_container_width=True):
            if os.path.exists(DB_PATH):
                try:
                    os.remove(DB_PATH)
                    if st.session_state.get("c_engine"):
                        try:
                            st.session_state.c_engine.sendline("EXIT")
                        except Exception:
                            pass
                        st.session_state.c_engine.close(force=True)
                        st.session_state.c_engine = None
                    st.success(" Database cleared!")
                    st.rerun()
                except Exception as e:
                    st.error(f"Error: {e}")
            else:
                st.info("Database is already empty.")
