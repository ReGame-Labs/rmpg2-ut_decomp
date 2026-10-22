#!/usr/bin/env python3
"""Progress toward a fully decompiled build, as a Markdown table with text progress bars.

Every output file already rebuilds byte-identical from split assembly; the percentages here are the share of game
code that is compiled from matching C (objdiff's matched code, in bytes). Psy-Q SDK code is excluded.

  tools/venv/bin/python tools/progress.py            # print the table (runs objdiff-cli report first)
  tools/venv/bin/python tools/progress.py --readme   # also rewrite docs/PROGRESS.md between the progress markers
  options: --no-report  use the existing build/report.json
The report, build/report.json, is also what decmp.dev reads (.github/workflows/ci.yml).
Adapted from gascarcella/dw2003recomp's tools/progress.py (MIT; docs/THIRD_PARTY.md).
"""
import argparse
import datetime
import json
import subprocess
import sys
from collections import defaultdict
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
REPORT = ROOT / "build/report.json"
README = ROOT / "docs" / "PROGRESS.md"
START, END = "<!-- progress:start -->", "<!-- progress:end -->"
WIDTH = 20

# Display names and order of the targets (objdiff unit names are "<target>/<unit>").
OVERLAYS: list[str] = []  # "overattr", "overmove" once they are targets


def bar(frac: float) -> str:
    full = int(frac * WIDTH)  # floor: a full bar means 100%
    return "█" * full + "░" * (WIDTH - full)


def row(name: str, matched: int, total: int, fmatched: int, ftotal: int) -> str:
    frac = matched / total if total else 0.0
    return f"| {name} | `{bar(frac)}` | {100 * frac:5.1f}% | {fmatched} / {ftotal} | {total:,} |"


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--readme", action="store_true")
    ap.add_argument("--no-report", action="store_true")
    args = ap.parse_args()

    if not args.no_report:
        subprocess.run([str(ROOT / "tools/bin/objdiff-cli"), "report", "generate", "-p", ".", "-o", str(REPORT)],
                       cwd=ROOT, check=True, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    rep = json.loads(REPORT.read_text())

    per_target = defaultdict(lambda: [0, 0, 0, 0])  # matched code, total code, matched funcs, total funcs
    for u in rep["units"]:
        cats = (u.get("metadata") or {}).get("progress_categories") or []
        if "sdk" in cats:
            continue
        m = u["measures"]
        t = per_target[u["name"].split("/")[0]]
        t[0] += int(m.get("matched_code", 0) or 0)
        t[1] += int(m.get("total_code", 0) or 0)
        t[2] += int(m.get("matched_functions", 0) or 0)
        t[3] += int(m.get("total_functions", 0) or 0)

    def total(names):
        acc = [0, 0, 0, 0]
        for n in names:
            for i, v in enumerate(per_target.get(n, [0, 0, 0, 0])):
                acc[i] += v
        return acc

    groups = [("**All game code**", list(per_target)), ("Executable (`SLUS_007.42`)", ["main"])]
    if OVERLAYS:
        groups.append((f"Overlays ({len(OVERLAYS)})", OVERLAYS))
    head = ["| Part | Progress | Matched | Functions | Code bytes |", "|---|---|---:|---:|---:|"]
    lines = head + [row(name, *total(names)) for name, names in groups]
    lines += [row(f"`{n.upper()}`", *per_target[n]) for n in OVERLAYS if n in per_target]
    today = datetime.date.today().isoformat()
    text = (f"_Code compiled from matching C (objdiff, Psy-Q SDK excluded); updated {today}. Every file already "
            f"rebuilds byte-identical from split assembly._\n\n" + "\n".join(lines) + "\n")
    print(text)

    if args.readme:
        md = README.read_text()
        a, b = md.index(START) + len(START), md.index(END)
        README.write_text(md[:a] + "\n" + text + md[b:])
        print(f"updated {README.relative_to(ROOT)}")


if __name__ == "__main__":
    sys.exit(main())
