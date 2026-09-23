#!/usr/bin/env python3

from __future__ import annotations

import argparse
import re
import subprocess
import sys
import tempfile
from pathlib import Path

GP_REL_RE = re.compile(r"%gp_rel\(\s*([A-Za-z_][A-Za-z0-9_]*)\s*\)")

GP_OPERAND_RE = re.compile(r"\b([A-Za-z_][A-Za-z0-9_]*)\s*\(\s*\$gp\s*\)")

EXTERN_RE = re.compile(
    r"^(\s*)\.extern\s+"
    r"([A-Za-z_][A-Za-z0-9_]*)"
    r"\s*,\s*([0-9]+)\s*$"
)

LABEL_RE = re.compile(r"^\s*([A-Za-z_][A-Za-z0-9_]*)\s*:\s*$")

SPACE_RE = re.compile(r"^\s*\.space\s+([0-9]+)\s*$")


def read_function(text: str, function: str) -> str:
    patterns = [
        re.compile(
            rf"^\s*glabel\s+{re.escape(function)}\s*$",
            re.MULTILINE,
        ),
        re.compile(
            rf"^\s*{re.escape(function)}\s*:\s*$",
            re.MULTILINE,
        ),
    ]

    start_match = None
    for pattern in patterns:
        start_match = pattern.search(text)
        if start_match:
            break

    if start_match is None:
        raise RuntimeError(f"Could not find {function} in reference assembly")

    start = start_match.end()

    end_match = re.search(
        r"^\s*endlabel\b",
        text[start:],
        re.MULTILINE,
    )

    if end_match:
        return text[start : start + end_match.start()]

    next_function = re.search(
        r"^\s*glabel\s+[A-Za-z_][A-Za-z0-9_]*\s*$",
        text[start:],
        re.MULTILINE,
    )

    if next_function:
        return text[start : start + next_function.start()]

    return text[start:]


def gp_references(reference_asm: Path, function: str) -> set[str]:
    text = reference_asm.read_text()
    body = read_function(text, function)

    result: set[str] = set()

    for match in GP_REL_RE.finditer(body):
        result.add(match.group(1))

    for match in GP_OPERAND_RE.finditer(body):
        result.add(match.group(1))

    return result


def parse_externs(
    gcc_asm: str,
    gp_symbols: set[str],
    small_data_limit: int,
) -> tuple[str, set[str]]:
    transformed: list[str] = []
    converted: set[str] = set()

    for line in gcc_asm.splitlines():
        match = EXTERN_RE.match(line)

        if match is None:
            transformed.append(line)
            continue

        indent, symbol, size_text = match.groups()
        size = int(size_text)

        # Only convert externally-defined objects which the original
        # function actually accesses through $gp and which fit the
        # compiler's small-data limit.
        if symbol in gp_symbols and 0 < size <= small_data_limit:
            transformed.append(f"{indent}.comm {symbol},{size}")
            converted.add(symbol)
        else:
            transformed.append(line)

    return "\n".join(transformed) + "\n", converted


def strip_generated_sbss(
    maspsx_output: str,
    generated_symbols: set[str],
) -> str:
    """
    maspsx turns .comm entries into .sbss labels.

    Remove only the storage generated for the .extern -> .comm
    conversions. Leave genuine function-local .sbss variables alone.
    """
    if not generated_symbols:
        return maspsx_output

    lines = maspsx_output.splitlines()
    result: list[str] = []

    in_sbss = False
    i = 0

    while i < len(lines):
        line = lines[i]
        stripped = line.strip()

        if stripped == ".section .sbss":
            in_sbss = True
            result.append(line)
            i += 1
            continue

        if (
            in_sbss
            and stripped.startswith(".section ")
            and stripped != ".section .sbss"
        ):
            in_sbss = False
            result.append(line)
            i += 1
            continue

        if in_sbss:
            # maspsx emits:
            #
            #   .align N
            #   SYMBOL:
            #       .space SIZE
            #
            # for small common symbols.
            if stripped.startswith(".align") and i + 2 < len(lines):
                label_match = LABEL_RE.match(lines[i + 1])
                space_match = SPACE_RE.match(lines[i + 2])

                if (
                    label_match is not None
                    and space_match is not None
                    and label_match.group(1) in generated_symbols
                ):
                    i += 3
                    continue

            # Also handle an entry without an explicit alignment.
            label_match = LABEL_RE.match(line)
            if label_match is not None and i + 1 < len(lines):
                space_match = SPACE_RE.match(lines[i + 1])

                if (
                    space_match is not None
                    and label_match.group(1) in generated_symbols
                ):
                    i += 2
                    continue

        result.append(line)
        i += 1

    return "\n".join(result) + "\n"


def run_maspsx(
    maspsx_script: Path,
    input_path: Path,
    aspsx_version: str,
    small_data_limit: int,
) -> str:
    command = [
        sys.executable,
        str(maspsx_script),
        f"--aspsx-version={aspsx_version}",
        f"-G{small_data_limit}",
        str(input_path),
    ]

    completed = subprocess.run(
        command,
        check=True,
        text=True,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
    )

    if completed.stderr:
        sys.stderr.write(completed.stderr)

    return completed.stdout


def main() -> int:
    parser = argparse.ArgumentParser(
        description=(
            "Prepare one GCC assembly file for the unmodified "
            "maspsx by restoring small-data handling for "
            "externally-defined game globals."
        )
    )

    parser.add_argument(
        "--gcc-asm",
        type=Path,
        required=True,
    )
    parser.add_argument(
        "--reference-asm",
        type=Path,
        required=True,
    )
    parser.add_argument(
        "--function",
        required=True,
    )
    parser.add_argument(
        "--output",
        type=Path,
        required=True,
    )
    parser.add_argument(
        "--maspsx",
        type=Path,
        default=Path("tools/maspsx/maspsx.py"),
    )
    parser.add_argument(
        "--aspsx-version",
        default="2.77",
    )
    parser.add_argument(
        "--small-data-limit",
        type=int,
        default=8,
    )

    args = parser.parse_args()

    gcc_asm = args.gcc_asm.read_text()

    gp_symbols = gp_references(
        args.reference_asm,
        args.function,
    )

    prepared_asm, converted = parse_externs(
        gcc_asm,
        gp_symbols,
        args.small_data_limit,
    )

    args.output.parent.mkdir(
        parents=True,
        exist_ok=True,
    )

    with tempfile.TemporaryDirectory(prefix="wild9-maspsx-") as tempdir:
        temp_input = Path(tempdir) / "input.s"
        temp_input.write_text(prepared_asm)

        maspsx_output = run_maspsx(
            args.maspsx.resolve(),
            temp_input,
            args.aspsx_version,
            args.small_data_limit,
        )

    final_asm = strip_generated_sbss(
        maspsx_output,
        converted,
    )

    args.output.write_text(final_asm)

    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except (
        RuntimeError,
        OSError,
        subprocess.CalledProcessError,
    ) as exc:
        print(
            f"error: {exc}",
            file=sys.stderr,
        )
        raise SystemExit(1)
