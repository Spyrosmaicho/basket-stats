def render_stat_bar(val1: float, val2: float) -> str:
    total = val1 + val2
    pct1 = round(val1 / total * 100) if total else 50
    pct2 = 100 - pct1
    c1 = "#22C55E" if val1 >= val2 else "#EF4444"
    c2 = "#22C55E" if val2 >= val1 else "#EF4444"
    return f"""
<div style="display:grid;grid-template-columns:1fr 1fr;gap:4px;margin-bottom:4px;">
  <div style="background:{c1};height:6px;border-radius:3px 0 0 3px;
    width:{pct1}%;margin-left:auto;"></div>
  <div style="background:{c2};height:6px;border-radius:0 3px 3px 0;
    width:{pct2}%;"></div>
</div>
"""
