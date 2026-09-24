#!/usr/bin/env python3
"""Sort func_XXXXXXXX declarations in a C header by address."""

import re
import sys
from pathlib import Path

DECLARATION = re.compile(r"(?m)^[^\n]*\bfunc_([0-9A-Fa-f]{8})\s*\([^\n]*\);\n?")


def sort_declarations(path: Path) -> None:
    text = path.read_text()
    matches = list(DECLARATION.finditer(text))
    if not matches:
        return

    ordered_matches = sorted(matches, key=lambda match: int(match.group(1), 16))
    declarations = [match.group() for match in ordered_matches]
    start, end = matches[0].start(), matches[-1].end()
    path.write_text(text[:start] + "".join(declarations) + text[end:])


if __name__ == "__main__":
    if len(sys.argv) != 2:
        raise SystemExit(f"Usage: {sys.argv[0]} HEADER")
    sort_declarations(Path(sys.argv[1]))
