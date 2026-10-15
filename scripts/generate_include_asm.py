#!/usr/bin/env python3
"""Regenerate src/main.c with one INCLUDE_ASM stub per function."""
from __future__ import annotations

import argparse
import re
import sys
from pathlib import Path

GLABEL_RE = re.compile(r"^glabel (func_[0-9A-Fa-f]+)\s*$")


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("src", type=Path, help="path to asm/800.s")
    ap.add_argument("out", type=Path, help="path to src/main.c")
    args = ap.parse_args()

    if not args.src.is_file():
        print(f"error: {args.src} does not exist", file=sys.stderr)
        return 1

    functions = [
        m.group(1)
        for line in args.src.read_text().splitlines()
        if (m := GLABEL_RE.match(line))
    ]

    with args.out.open("w") as f:
        f.write('#include "types.h"\n')
        f.write('#include "include_asm.h"\n\n')
        for name in functions:
            f.write(f'INCLUDE_ASM("asm/nonmatchings/main", {name});\n')

    print(f"wrote {len(functions)} INCLUDE_ASM stubs to {args.out}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())