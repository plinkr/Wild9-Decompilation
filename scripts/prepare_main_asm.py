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


def gp_references(reference_asm: Path) -> set[str]:
    text = reference_asm.read_text()

    result: set[str] = set()

    for match in GP_REL_RE.finditer(text):
        result.add(match.group(1))

    for match in GP_OPERAND_RE.finditer(text):
        result.add(match.group(1))

    return result


def prepare_externs(
    gcc_asm: str,
    gp_symbols: set[str],
    small_data_limit: int,
) -> tuple[str, set[str]]:
    result: list[str] = []
    converted: set[str] = set()

    for line in gcc_asm.splitlines():
        match = EXTERN_RE.match(line)

        if match is None:
            result.append(line)
            continue

        indent, symbol, size_text = match.groups()
        size = int(size_text)

        if symbol in gp_symbols and 0 < size <= small_data_limit:
            result.append(f"{indent}.comm {symbol},{size}")
            converted.add(symbol)
        else:
            result.append(line)

    return (
        "\n".join(result) + "\n",
        converted,
    )


def strip_generated_sbss(
    maspsx_output: str,
    generated_symbols: set[str],
) -> str:
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
    maspsx: Path,
    input_path: Path,
    aspsx_version: str,
    small_data_limit: int,
) -> str:
    completed = subprocess.run(
        [
            sys.executable,
            str(maspsx),
            f"--aspsx-version={aspsx_version}",
            f"-G{small_data_limit}",
            str(input_path),
        ],
        check=True,
        text=True,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
    )

    if completed.stderr:
        sys.stderr.write(completed.stderr)

    return completed.stdout


def main() -> int:
    parser = argparse.ArgumentParser()

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
        "--output",
        type=Path,
        required=True,
    )
    parser.add_argument(
        "--maspsx",
        type=Path,
        required=True,
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

    gp_symbols = gp_references(args.reference_asm)

    prepared_asm, converted = prepare_externs(
        gcc_asm,
        gp_symbols,
        args.small_data_limit,
    )

    with tempfile.TemporaryDirectory(prefix="wild9-main-maspsx-") as tempdir:
        temp_input = Path(tempdir) / "main.s"

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

    args.output.parent.mkdir(
        parents=True,
        exist_ok=True,
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
