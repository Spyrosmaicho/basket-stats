import os
import sys
import subprocess
import streamlit as st
from config import RUN_DIR


def compile_c() -> bool:
    try:
        if not os.path.exists(RUN_DIR):
            st.error(f"Build directory not found → {RUN_DIR}")
            return False
        res = subprocess.run(["make"], cwd=RUN_DIR, capture_output=True, text=True)
        if res.returncode != 0:
            st.error("Compilation failed (Make Error)!")
            st.code(res.stderr)
            return False
        return True
    except Exception as e:
        st.error(f"Make command error: {e}")
        return False


def start_daemon():
    import pexpect

    if "c_engine" not in st.session_state:
        st.session_state.c_engine = None

    if st.session_state.c_engine is None or not st.session_state.c_engine.isalive():
        if not compile_c():
            return False
        exe_path = os.path.join(RUN_DIR, "basket")
        st.session_state.c_engine = pexpect.spawn(
            f"{exe_path} --daemon",
            cwd=RUN_DIR,
            encoding="utf-8",
            timeout=15,
        )
        st.session_state.c_engine.setecho(False)
        st.session_state.c_engine.logfile = sys.stdout
        st.session_state.c_engine.expect("DAEMON_READY")

    return st.session_state.c_engine


def send_command(cmd: str):
    try:
        child = start_daemon()
        if child:
            child.sendline(cmd)
            index = child.expect(["OK", "ERROR: "])
            if index == 0:
                return True, "Success"
            else:
                error_msg = child.readline().strip()
                return False, error_msg
        return False, "Daemon not running."
    except Exception as e:
        st.error(f"Engine Communication Error: {e}")
        st.session_state.c_engine = None
        return False, "Connection crashed."
