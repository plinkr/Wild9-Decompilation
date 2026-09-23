#!/usr/bin/env python3
"""Generate objdiff.json for the Wild 9 main executable."""

from __future__ import annotations

import json
from pathlib import Path
from typing import TypedDict

ROOT = Path(__file__).resolve().parents[1]
ASM_DIR = ROOT / "asm" / "nonmatchings" / "main"
SRC_DIR = ROOT / "src" / "functions"
OUTPUT = ROOT / "objdiff.json"
TARGET_DIR = "build/objdiff/target"
BASE_DIR = "build/functions"


class Metadata(TypedDict, total=False):
    progress_categories: list[str]
    source_path: str


class Unit(TypedDict, total=False):
    name: str
    target_path: str
    base_path: str
    metadata: Metadata


def main() -> int:
    asm_files = sorted(ASM_DIR.glob("func_*.s"))
    if not asm_files:
        raise SystemExit(
            f"No func_*.s files found in {ASM_DIR}. Run 'make split' first."
        )

    units: list[Unit] = []

    for asm_path in asm_files:
        name = asm_path.stem
        source_path = SRC_DIR / f"{name}.c"

        metadata: Metadata = {
            "progress_categories": ["main"],
        }

        unit: Unit = {
            "name": f"main/{name}",
            "target_path": f"{TARGET_DIR}/{name}.o",
            "metadata": metadata,
        }

        if source_path.is_file():
            unit["base_path"] = f"{BASE_DIR}/{name}.o"
            metadata["source_path"] = f"src/functions/{name}.c"

        units.append(unit)

    config = {
        "$schema": (
            "https://raw.githubusercontent.com/encounter/objdiff/"
            "main/config.schema.json"
        ),
        "custom_make": "make",
        "build_target": False,
        "build_base": True,
        "watch_patterns": [
            "*.c",
            "*.h",
            "*.s",
            "*.inc",
            "*.py",
            "Makefile",
        ],
        "ignore_patterns": ["build/**/*"],
        "units": units,
        "progress_categories": [
            {
                "id": "main",
                "name": "Wild 9 NTSC-U",
            }
        ],
    }

    OUTPUT.write_text(
        json.dumps(config, indent=2) + "\n",
        encoding="utf-8",
    )

    with_source = sum("base_path" in unit for unit in units)

    print(f"Wrote {OUTPUT}")
    print(f"Functions in target: {len(units)}")
    print(f"Functions with C base: {with_source}")
    print(f"Assembly-only functions: {len(units) - with_source}")

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
