#!/usr/bin/env python3
"""Extract the PS-X EXE (boot executable) from a Redump-style PS1 .cue/.bin

Usage:
    python3 extract_psx_exe.py "Wild 9 (USA).cue"
    python3 extract_psx_exe.py "Wild 9 (USA).bin"
    python3 extract_psx_exe.py "Wild 9 (USA).cue" SLUS_004.25

Redump filenames contain spaces and parentheses, so always quote the path
(or let your shell's tab-completion escape it for you):

    python3 extract_psx_exe.py "/path/to/your/ROMS/Wild 9/Wild 9 (USA).bin"

Works with MODE2/2352 raw dumps (typical .bin) and cooked 2048-byte ISOs.
"""
from __future__ import annotations
import re, struct, sys
from pathlib import Path

DST_SEC = 2352       # raw sector size
USER = 2048          # user data bytes per sector
USER_OFF = 24        # offset of user data inside a raw MODE2 sector
SYNC = bytes([0x00] + [0xFF] * 10 + [0x00])



def parse_cue(cue_path: Path) -> tuple[str, str]:
    """Return (track1_file, track1_kind) from a .cue."""
    text = cue_path.read_text(encoding="utf-8", errors="replace")
    current_file = ""
    for raw in text.splitlines():
        line = raw.strip()
        m = re.match(r'FILE\s+"([^"]+)"', line, re.I) or re.match(r"FILE\s+(\S+)", line, re.I)
        if m:
            current_file = m.group(1)
            continue
        m = re.match(r"TRACK\s+01\s+(\S+)", line, re.I)
        if m:
            return current_file, m.group(1).upper()
    raise SystemExit(f"no TRACK 01 in cue: {cue_path}")


def resolve_bin(cue_path: Path, name: str) -> Path:
    p = (cue_path.parent / name.replace("\\", "/")).resolve()
    if p.is_file():
        return p
    for child in p.parent.iterdir():
        if child.is_file() and child.name.lower() == p.name.lower():
            return child
    raise SystemExit(f"missing bin: {p}")



def read_user_raw(data: bytes, lba: int) -> bytes:
    off = lba * DST_SEC
    if data[off:off + 12] != SYNC:
        raise KeyError(lba)
    return data[off + USER_OFF: off + USER_OFF + USER]


def read_user_cooked(data: bytes, lba: int) -> bytes:
    off = lba * USER
    return data[off: off + USER]


def parse_root(pvd_root: bytes) -> dict[str, tuple[int, int]]:
    entries: dict[str, tuple[int, int]] = {}
    i = 0
    while i < len(pvd_root):
        reclen = pvd_root[i]
        if reclen == 0:
            i = ((i // USER) + 1) * USER
            if i >= len(pvd_root):
                break
            continue
        extent = struct.unpack_from("<I", pvd_root, i + 2)[0]
        size = struct.unpack_from("<I", pvd_root, i + 10)[0]
        namelen = pvd_root[i + 32]
        name = pvd_root[i + 33:i + 33 + namelen]
        if b";" in name:
            name = name.split(b";")[0]
        if name not in (b"\x00", b"\x01"):
            entries[name.decode("ascii", "replace")] = (extent, size)
        i += reclen
    return entries


def read_file(read_user, data: bytes, extent: int, size: int) -> bytes:
    out = bytearray()
    lba, rem = extent, size
    while rem > 0:
        sec = read_user(data, lba)
        take = min(USER, rem)
        out += sec[:take]
        rem -= take
        lba += 1
    return bytes(out)


def parse_system_cnf(cnf: bytes) -> str:
    text = cnf.decode("ascii", "replace")
    m = re.search(r"BOOT\s*=\s*cdrom:\\?([^;\s]+)", text, re.I)
    if not m:
        raise SystemExit("SYSTEM.CNF has no BOOT= line")
    token = m.group(1).strip()
    return token.split("\\")[-1].split("/")[-1]


def normalize_exe_name(token: str) -> str:
    """SLUS_005.62  ->  SLUS_005.62 (uppercase, canonical form)."""
    s = "".join(c for c in token.upper() if c.isalnum())
    if len(s) >= 9 and not ("_" in token and "." in token):
        return f"{s[:4]}_{s[4:7]}.{s[7:9]}"
    return token.upper()



def extract(cue_or_bin: Path, out: Path | None = None) -> Path:
    src = cue_or_bin.resolve()

    if src.suffix.lower() == ".cue":
        bin_name, _ = parse_cue(src)
        bin_path = resolve_bin(src, bin_name)
    else:
        bin_path = src

    print(f"[*] data track: {bin_path.name} ({bin_path.stat().st_size} bytes)")
    data = bin_path.read_bytes()

    cooked = (
        len(data) >= 17 * USER
        and data[16 * USER + 1: 16 * USER + 6] == b"CD001"
        and not (len(data) >= 17 * DST_SEC
                 and data[16 * DST_SEC: 16 * DST_SEC + 12] == SYNC)
    )
    read_user = read_user_cooked if cooked else read_user_raw
    print(f"[*] sector layout: {'cooked 2048' if cooked else 'raw MODE2/2352'}")

    pvd = read_user(data, 16)
    if pvd[1:6] != b"CD001":
        raise SystemExit("PVD not found at LBA 16")

    root_extent = struct.unpack_from("<I", pvd, 158)[0]
    root_size = struct.unpack_from("<I", pvd, 166)[0]
    root = b"".join(
        read_user(data, root_extent + i)
        for i in range((root_size + USER - 1) // USER)
    )[:root_size]
    entries = parse_root(root)

    # SYSTEM.CNF (or PSX.EXE fallback for very early titles)
    if "SYSTEM.CNF" in entries:
        ext, sz = entries["SYSTEM.CNF"]
        token = parse_system_cnf(read_file(read_user, data, ext, sz))
    else:
        psx = next((k for k in entries if k.upper() == "PSX.EXE"), None)
        if not psx:
            raise SystemExit("no SYSTEM.CNF and no PSX.EXE on disc")
        token = psx

    exe_name = normalize_exe_name(token)
    # Find the actual entry on disc (case-insensitive)
    disc_name = next(
        (k for k in entries if k.upper() in (token.upper(), exe_name.upper())),
        None,
    )
    if not disc_name:
        raise SystemExit(f"boot EXE {token!r} not found on disc")

    ext, sz = entries[disc_name]
    exe = read_file(read_user, data, ext, sz)
    if exe[:8] != b"PS-X EXE":
        raise SystemExit(f"{disc_name} is not a PS-X EXE")

    dest = out or (Path.cwd() / exe_name)
    dest.write_bytes(exe)
    print(f"[+] wrote {dest} ({len(exe)} bytes)")
    return dest


def main() -> int:
    if len(sys.argv) < 2:
        print(__doc__)
        return 2
    src = Path(sys.argv[1]).expanduser()
    out = Path(sys.argv[2]).expanduser() if len(sys.argv) > 2 else None
    if not src.is_file():
        print(f"not found: {src}", file=sys.stderr)
        return 1
    extract(src, out)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
