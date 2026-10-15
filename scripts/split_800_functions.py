#!/usr/bin/env python3
"""Split asm/800.s into one file per function under asm/nonmatchings/main/."""
from __future__ import annotations

import argparse
import re
import sys
from pathlib import Path

GLABEL_RE = re.compile(r"^glabel (func_[0-9A-Fa-f]+)\s*$")


def split(src: Path, out_dir: Path) -> int:
    if not src.is_file():
        print(f"error: {src} does not exist", file=sys.stderr)
        return 1

    out_dir.mkdir(parents=True, exist_ok=True)
    lines = src.read_text().splitlines(keepends=True)

    i = 0
    count = 0
    while i < len(lines):
        m = GLABEL_RE.match(lines[i].rstrip())
        if not m:
            i += 1
            continue

        name = m.group(1)
        start = i
        while i < len(lines):
            if lines[i].strip() == f"endlabel {name}":
                i += 1
                break
            i += 1

        (out_dir / f"{name}.s").write_text("".join(lines[start:i]))
        count += 1

    print(f"split {src}: wrote {count} functions to {out_dir}")
    return 0


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("src", type=Path, help="path to asm/800.s")
    ap.add_argument("out_dir", type=Path, help="output directory")
    args = ap.parse_args()
    return split(args.src, args.out_dir)


if __name__ == "__main__":
    raise SystemExit(main())