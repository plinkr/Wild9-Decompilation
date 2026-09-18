#!/usr/bin/env python3
import struct
import sys
from pathlib import Path


def u32(data: bytes, offset: int) -> int:
    return struct.unpack_from("<I", data, offset)[0]


def main() -> int:
    if len(sys.argv) != 2:
        print(f"usage: {sys.argv[0]} SLUS_004.25", file=sys.stderr)
        return 2

    path = Path(sys.argv[1])
    data = path.read_bytes()

    if len(data) < 0x30:
        print(f"error: file is too small to be a PS-X EXE: {len(data)} bytes", file=sys.stderr)
        return 1

    print(f"file       : {path}")
    print(f"size       : 0x{len(data):X} ({len(data)} bytes)")
    print(f"magic      : {data[:8]!r}")
    print(f"pc0        : 0x{u32(data, 0x10):08X}")
    print(f"gp0        : 0x{u32(data, 0x14):08X}")
    print(f"t_addr     : 0x{u32(data, 0x18):08X}")
    print(f"t_size     : 0x{u32(data, 0x1C):08X}")
    print(f"d_addr     : 0x{u32(data, 0x20):08X}")
    print(f"d_size     : 0x{u32(data, 0x24):08X}")
    print(f"b_addr     : 0x{u32(data, 0x28):08X}")
    print(f"b_size     : 0x{u32(data, 0x2C):08X}")
    print(f"stack_base : 0x{u32(data, 0x30):08X}" if len(data) >= 0x34 else "stack_base : unavailable")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
