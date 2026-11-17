#!/usr/bin/env python3
"""Generate objdiff.json for the Wild 9 main executable.

Every function belongs to the "main" category and to either "game" or "sdk"
(the Sony library code linked after the game, see layout.SDK_START). Functions
listed in config/handwritten_functions.txt were assembly in the original and
also belong to "handwritten": their base object is the target object itself,
so they count as matched and complete.
"""

from __future__ import annotations

import json
from pathlib import Path
from typing import TypedDict

from layout import is_sdk_function

ROOT = Path(__file__).resolve().parents[1]
ASM_DIR = ROOT / "asm" / "nonmatchings" / "main"
SRC_DIR = ROOT / "src" / "functions"
HANDWRITTEN_LIST = ROOT / "config" / "handwritten_functions.txt"
OUTPUT = ROOT / "objdiff.json"
TARGET_DIR = "build/objdiff/target"
BASE_DIR = "build/functions"


class Metadata(TypedDict, total=False):
    complete: bool
    progress_categories: list[str]
    source_path: str


class Unit(TypedDict, total=False):
    name: str
    target_path: str
    base_path: str
    metadata: Metadata


def read_handwritten() -> set[str]:
    names: set[str] = set()
    for line in HANDWRITTEN_LIST.read_text(encoding="utf-8").splitlines():
        name = line.split("#", 1)[0].strip()
        if name:
            names.add(name)
    return names


def main() -> int:
    asm_files = sorted(ASM_DIR.glob("func_*.s"))
    if not asm_files:
        raise SystemExit(
            f"No func_*.s files found in {ASM_DIR}. Run 'make split' first."
        )

    handwritten = read_handwritten()
    known = {path.stem for path in asm_files}
    unknown = sorted(handwritten - known)
    if unknown:
        raise SystemExit(
            f"{HANDWRITTEN_LIST.name} lists unknown functions: {', '.join(unknown)}"
        )

    units: list[Unit] = []

    for asm_path in asm_files:
        name = asm_path.stem
        source_path = SRC_DIR / f"{name}.c"
        region = "sdk" if is_sdk_function(name) else "game"

        metadata: Metadata = {
            "progress_categories": ["main", region],
        }

        unit: Unit = {
            "name": f"main/{name}",
            "target_path": f"{TARGET_DIR}/{name}.o",
            "metadata": metadata,
        }

        if name in handwritten:
            if source_path.is_file():
                raise SystemExit(
                    f"{name} is listed as hand-written but has {source_path}"
                )
            unit["base_path"] = unit["target_path"]
            metadata["complete"] = True
            metadata["progress_categories"].append("handwritten")
        elif source_path.is_file():
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
            {"id": "main", "name": "Wild 9 NTSC-U"},
            {"id": "game", "name": "Game code"},
            {"id": "sdk", "name": "Sony library"},
            {"id": "handwritten", "name": "Hand-written assembly"},
        ],
    }

    OUTPUT.write_text(
        json.dumps(config, indent=2) + "\n",
        encoding="utf-8",
    )

    with_source = sum("source_path" in unit["metadata"] for unit in units)

    print(f"Wrote {OUTPUT}")
    print(f"Functions in target: {len(units)}")
    print(f"Functions with C base: {with_source}")
    print(f"Hand-written assembly: {len(handwritten)}")
    print(f"Assembly-only functions: {len(units) - with_source - len(handwritten)}")

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
