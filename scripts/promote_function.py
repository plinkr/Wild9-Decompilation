#!/usr/bin/env python3

from __future__ import annotations

import re
import sys
from pathlib import Path


FUNCTION_RE = re.compile(
    r"^func_([0-9A-Fa-f]{8})$"
)

INCLUDE_ASM_RE = re.compile(
    r'^[ \t]*INCLUDE_ASM\(\s*'
    r'"asm/nonmatchings/main"\s*,\s*'
    r'([A-Za-z_][A-Za-z0-9_]*)\s*\)\s*;\s*$'
)

C_INCLUDE_RE = re.compile(
    r'^[ \t]*#include\s+"functions/'
    r'([A-Za-z_][A-Za-z0-9_]*)\.c"\s*$'
)


def function_address(name: str) -> int:
    match = FUNCTION_RE.fullmatch(name)

    if match is None:
        raise RuntimeError(
            f"Function name is not func_XXXXXXXX: {name}"
        )

    return int(match.group(1), 16)


def entry_name(line: str) -> str | None:
    match = INCLUDE_ASM_RE.match(line)

    if match is not None:
        return match.group(1)

    match = C_INCLUDE_RE.match(line)

    if match is not None:
        return match.group(1)

    return None


def main() -> int:
    if len(sys.argv) != 3:
        print(
            f"usage: {sys.argv[0]} <main.c> <function>",
            file=sys.stderr,
        )
        return 2

    main_c = Path(sys.argv[1])
    function = sys.argv[2]
    function_file = (
        main_c.parent / "functions" / f"{function}.c"
    )

    if not function_file.is_file():
        raise RuntimeError(
            f"Missing function source: {function_file}"
        )

    target_address = function_address(function)

    lines = main_c.read_text().splitlines(
        keepends=True
    )

    # Already promoted.
    for line in lines:
        if C_INCLUDE_RE.match(line):
            name = entry_name(line)

            if name == function:
                print(
                    f"{function}: already promoted"
                )
                return 0

    # Replace the original INCLUDE_ASM placeholder when it exists.
    for index, line in enumerate(lines):
        match = INCLUDE_ASM_RE.match(line)

        if (
            match is not None
            and match.group(1) == function
        ):
            lines[index] = (
                f'#include "functions/{function}.c"\n'
            )

            main_c.write_text(
                "".join(lines)
            )

            print(
                f"{function}: promoted in {main_c}"
            )
            return 0

    # The current main.c can legitimately be missing a placeholder
    # for a standalone function. Insert it in address order.
    for index, line in enumerate(lines):
        name = entry_name(line)

        if name is None:
            continue

        candidate_address = function_address(name)

        if candidate_address > target_address:
            lines.insert(
                index,
                f'#include "functions/{function}.c"\n',
            )

            main_c.write_text(
                "".join(lines)
            )

            print(
                f"{function}: promoted in {main_c}"
            )
            return 0

    # Function belongs after the final function entry.
    if lines and not lines[-1].endswith("\n"):
        lines[-1] += "\n"

    lines.append(
        f'#include "functions/{function}.c"\n'
    )

    main_c.write_text(
        "".join(lines)
    )

    print(
        f"{function}: promoted in {main_c}"
    )

    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(
            main()
        )
    except RuntimeError as exc:
        print(
            f"error: {exc}",
            file=sys.stderr,
        )
        raise SystemExit(1)
