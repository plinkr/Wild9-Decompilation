#!/usr/bin/env python3
"""Sort and deduplicate func_XXXXXXXX and D_XXXXXXXX declarations."""

import re
import sys
from pathlib import Path

DECLARATION = re.compile(
    r"""(?mx)
    ^
    (?P<decl>
        (?:
            [^\n]*\bfunc_([0-9A-Fa-f]{8})\b[^\n]*;
            |
            [ \t]*extern[^\n]*\bD_([0-9A-Fa-f]{8})\b[^\n]*;
        )
    )
    [ \t]*
    (?P<comment>//[^\n]*)?
    (?P<newline>\n|$)
    """
)

SYMBOL = re.compile(r"\b(func_|D_)([0-9A-Fa-f]{8})\b")


def normalize_comment(comment: str | None) -> str:
    if not comment:
        return ""
    return comment.strip()


def declaration_key(decl: str) -> tuple[str, int]:
    match = SYMBOL.search(decl)
    if not match:
        raise ValueError(f"Could not determine declaration address: {decl!r}")

    return match.group(1), int(match.group(2), 16)


def declaration_code(match: re.Match[str]) -> str:
    return match.group("decl").rstrip()


def format_declaration(
    decl: str,
    comment: str,
    newline: str,
) -> str:
    if comment:
        return f"{decl.rstrip()} {comment.strip()}{newline}"
    return f"{decl.rstrip()}{newline}"


def sort_declarations(path: Path) -> None:
    text = path.read_text()

    matches = list(DECLARATION.finditer(text))
    if not matches:
        return

    # Make sure the sortable region does not contain unrelated text.
    start = matches[0].start()
    end = matches[-1].end()
    region = text[start:end]

    covered = "".join(match.group() for match in matches)

    if region != covered:
        raise SystemExit(
            f"{path}: declarations are not in one contiguous block; "
            "refusing to reorder to avoid deleting unrelated comments or code."
        )

    declarations: dict[tuple[str, int], tuple[str, str, str]] = {}

    for match in matches:
        decl = declaration_code(match)
        comment = normalize_comment(match.group("comment"))
        newline = match.group("newline")

        key = declaration_key(decl)

        if key not in declarations:
            declarations[key] = (decl, comment, newline)
            continue

        previous_decl, previous_comment, _ = declarations[key]

        if previous_decl != decl:
            prefix, address = key
            symbol = f"{prefix}{address:08X}"
            raise SystemExit(
                f"{path}: conflicting declarations for {symbol}:\n"
                f"  {previous_decl};"
                + (f" {previous_comment}" if previous_comment else "")
                + "\n"
                f"  {decl};" + (f" {comment}" if comment else "")
            )

        # Same declaration: preserve the comment if only one copy has it.
        if previous_comment and comment and previous_comment != comment:
            prefix, address = key
            symbol = f"{prefix}{address:08X}"
            raise SystemExit(
                f"{path}: conflicting comments for {symbol}:\n"
                f"  {previous_comment}\n"
                f"  {comment}"
            )

        if not previous_comment and comment:
            declarations[key] = (previous_decl, comment, newline)

    ordered = sorted(
        declarations.values(),
        key=lambda item: declaration_key(item[0]),
    )

    output = "".join(
        format_declaration(decl, comment, newline) for decl, comment, newline in ordered
    )

    path.write_text(text[:start] + output + text[end:])


def main() -> None:
    if len(sys.argv) < 2:
        raise SystemExit(f"Usage: {sys.argv[0]} HEADER [HEADER ...]")

    for argument in sys.argv[1:]:
        sort_declarations(Path(argument))


if __name__ == "__main__":
    main()
