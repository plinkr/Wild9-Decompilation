#!/usr/bin/env python3

from __future__ import annotations

import struct
import subprocess
import sys
from pathlib import Path

NM = "mipsel-linux-gnu-nm"


def run(*args: str) -> str:
    return subprocess.check_output(args, text=True)


def symbol(path: Path, name: str) -> tuple[int, int]:
    for line in run(NM, "-S", "-n", str(path)).splitlines():
        fields = line.split(None, 3)
        if len(fields) != 4 or fields[3] != name:
            continue
        return int(fields[0], 16), int(fields[1], 16)
    raise RuntimeError(f"symbol not found: {name}")


def psx_load_address(exe: Path) -> int:
    with exe.open("rb") as f:
        f.seek(0x18)
        return struct.unpack("<I", f.read(4))[0]


def main() -> int:
    if len(sys.argv) != 5:
        print(
            f"usage: {sys.argv[0]} <function> <original-exe> <original-elf> <function-bin>",
            file=sys.stderr,
        )
        return 2

    function = sys.argv[1]
    original_exe = Path(sys.argv[2])
    original_elf = Path(sys.argv[3])
    function_bin = Path(sys.argv[4])

    address, expected_size = symbol(original_elf, function)
    actual = function_bin.read_bytes()
    if len(actual) != expected_size:
        raise RuntimeError(
            f"{function}: generated size 0x{len(actual):X} != original size 0x{expected_size:X}"
        )

    load_address = psx_load_address(original_exe)
    file_offset = 0x800 + (address - load_address)

    with original_exe.open("rb") as f:
        f.seek(file_offset)
        expected = f.read(len(actual))

    if expected == actual:
        print(f"{function}: MATCH")
        return 0

    print(f"{function}: MISMATCH")
    print("First differences:")
    count = 0
    for i, (a, b) in enumerate(zip(expected, actual), start=1):
        if a != b:
            print(f"{i:6d} {a:3d} {b:3d}")
            count += 1
            if count >= 40:
                break
    return 1


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except (RuntimeError, subprocess.CalledProcessError) as exc:
        print(f"error: {exc}", file=sys.stderr)
        raise SystemExit(1)
