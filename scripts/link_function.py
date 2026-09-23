#!/usr/bin/env python3

from __future__ import annotations

import re
import subprocess
import sys
import tempfile
from pathlib import Path

NM = "mipsel-linux-gnu-nm"
READELF = "mipsel-linux-gnu-readelf"
LD = "mipsel-linux-gnu-ld"
OBJCOPY = "mipsel-linux-gnu-objcopy"

ADDRESS_SYMBOL_RE = re.compile(r"^(?:func|D|DAT|PTR)_([0-9A-Fa-f]{8})$")


def run(*args: str) -> str:
    return subprocess.check_output(
        args,
        text=True,
    )


def nm_defined(
    path: Path,
) -> dict[str, tuple[int, int, str]]:
    """
    Return defined symbols from an ELF/object:

        name -> (address, size, type)
    """
    result: dict[str, tuple[int, int, str]] = {}

    for line in run(
        NM,
        "-S",
        "-n",
        str(path),
    ).splitlines():
        fields = line.split(None, 3)

        if len(fields) != 4:
            continue

        value, size, sym_type, name = fields

        if sym_type in ("U", "u"):
            continue

        try:
            result[name] = (
                int(value, 16),
                int(size, 16),
                sym_type,
            )
        except ValueError:
            continue

    return result


def nm_undefined(path: Path) -> list[str]:
    """
    Return undefined symbols from an object.
    """
    names: list[str] = []

    for line in run(
        NM,
        "-u",
        str(path),
    ).splitlines():
        fields = line.split()

        if not fields:
            continue

        names.append(fields[-1])

    return names


def section_sizes(path: Path) -> dict[str, int]:
    """
    Parse:

        readelf -WS file.o

    Section columns are:

        [Nr] Name Type Address Offset Size EntFlg ...
    """
    result: dict[str, int] = {}

    for line in run(
        READELF,
        "-WS",
        str(path),
    ).splitlines():
        match = re.match(
            r"\s*\[\s*\d+\]\s+"
            r"(\S+)\s+"
            r"\S+\s+"
            r"\S+\s+"
            r"\S+\s+"
            r"\S+\s+"
            r"([0-9A-Fa-f]+)",
            line,
        )

        if not match:
            continue

        result[match.group(1)] = int(
            match.group(2),
            16,
        )

    return result


def parse_gp(
    linker_script: Path,
    original_elf: Path,
) -> int:
    """
    Determine the original link-time $gp.

    Prefer _gp from the project linker script.
    Fall back to ELF symbols.
    """
    text = linker_script.read_text()

    patterns = (
        r"\b_gp\s*=\s*(0x[0-9A-Fa-f]+)\s*;",
        r"\b_gp\s*=\s*([0-9A-Fa-f]+)\s*;",
    )

    for pattern in patterns:
        match = re.search(
            pattern,
            text,
        )

        if match:
            return int(
                match.group(1),
                0,
            )

    symbols = nm_defined(original_elf)

    for name in (
        "_gp",
        "__gnu_local_gp",
    ):
        entry = symbols.get(name)

        if entry is not None:
            return entry[0]

    raise RuntimeError(
        f"Could not determine _gp from {linker_script} or {original_elf}"
    )


def resolve_symbol_address(
    symbol: str,
    original: dict[str, tuple[int, int, str]],
) -> int | None:
    """
    Resolve an undefined symbol.

    Functions use the address from the original ELF.

    Data/global symbols with an address encoded in their name
    use that encoded address directly. This is important for
    aliases such as D_80077488 whose ELF symbol may be located
    at a nearby address.
    """
    match = ADDRESS_SYMBOL_RE.fullmatch(symbol)

    if match is not None:
        prefix = symbol.split("_", 1)[0]
        encoded_address = int(match.group(1), 16)

        if prefix in ("D", "DAT", "PTR"):
            return encoded_address

    entry = original.get(symbol)

    if entry is not None:
        return entry[0]

    if match is not None:
        return int(match.group(1), 16)

    return None


def discard_script() -> str:
    return """    /DISCARD/ :
    {
        *(.reginfo)
        *(.MIPS.abiflags)
        *(.pdr)
        *(.gnu.attributes)
        *(.comment)
        *(.note*)
    }
"""


def main() -> int:
    if len(sys.argv) != 6:
        print(
            f"usage: {sys.argv[0]} "
            f"<function> <object> <original-elf> "
            f"<project-ld> <output>",
            file=sys.stderr,
        )
        return 2

    function = sys.argv[1]
    obj = Path(sys.argv[2]).resolve()
    original_elf = Path(sys.argv[3]).resolve()
    project_ld = Path(sys.argv[4]).resolve()
    output = Path(sys.argv[5]).resolve()

    # ---------------------------------------------------------------
    # Original symbols
    # ---------------------------------------------------------------

    original = nm_defined(original_elf)

    function_entry = original.get(function)

    if function_entry is None:
        raise RuntimeError(f"Function not found in original ELF: {function}")

    function_address, function_size, function_type = function_entry

    if function_type not in ("T", "t"):
        raise RuntimeError(f"Original symbol is not text: {function}")

    # ---------------------------------------------------------------
    # Function object must contain text only.
    #
    # Game globals are extern and resolved below.
    # ---------------------------------------------------------------

    sections = section_sizes(obj)

    forbidden_sections = {
        ".sdata",
        ".sbss",
        ".data",
        ".bss",
        ".rodata",
        ".lit4",
        ".lit8",
    }

    forbidden = {
        name: size
        for name, size in sections.items()
        if name in forbidden_sections and size != 0
    }

    if forbidden:
        detail = ", ".join(
            f"{name}=0x{size:X}" for name, size in sorted(forbidden.items())
        )

        raise RuntimeError(
            f"{function}: function object contains data sections "
            f"({detail}). "
            "Game globals must be declared extern in globals.h; "
            "do not define storage in the function file."
        )

    # ---------------------------------------------------------------
    # GP
    # ---------------------------------------------------------------

    gp = parse_gp(
        project_ld,
        original_elf,
    )

    # ---------------------------------------------------------------
    # Resolve undefined symbols.
    # ---------------------------------------------------------------

    undefined = sorted(set(nm_undefined(obj)))

    ld_args: list[str] = [
        f"--defsym=_gp=0x{gp:08X}",
    ]

    for symbol in undefined:
        address = resolve_symbol_address(
            symbol,
            original,
        )

        if address is None:
            raise RuntimeError(
                f"{function}: undefined symbol '{symbol}' "
                "was not found in the original ELF and "
                "its address cannot be inferred from its name"
            )

        ld_args.append(f"--defsym={symbol}=0x{address:08X}")

    # ---------------------------------------------------------------
    # Temporary linker script.
    #
    # Only the function's .text is placed here.
    # ---------------------------------------------------------------

    script = f"""SECTIONS
{{
    .text 0x{function_address:08X} : SUBALIGN(1)
    {{
        "{obj.as_posix()}"(.text)
    }}
{discard_script()}}}
"""

    output.parent.mkdir(
        parents=True,
        exist_ok=True,
    )

    with tempfile.TemporaryDirectory(prefix="wild9-link-") as tempdir:
        tempdir_path = Path(tempdir)

        script_path = tempdir_path / "function.ld"

        elf_path = tempdir_path / "function.elf"

        script_path.write_text(script)

        # -----------------------------------------------------------
        # Link function at its original VRAM.
        # -----------------------------------------------------------

        subprocess.run(
            [
                LD,
                "-EL",
                "-nostdlib",
                "-G8",
                "--no-check-sections",
                *ld_args,
                "-T",
                str(script_path),
                "-o",
                str(elf_path),
                str(obj),
            ],
            check=True,
        )

        # -----------------------------------------------------------
        # Extract only .text.
        # -----------------------------------------------------------

        subprocess.run(
            [
                OBJCOPY,
                "-j",
                ".text",
                "-O",
                "binary",
                str(elf_path),
                str(output),
            ],
            check=True,
        )

    # ---------------------------------------------------------------
    # Final size sanity check.
    # ---------------------------------------------------------------

    actual_size = output.stat().st_size

    if actual_size != function_size:
        raise RuntimeError(
            f"{function}: linked text size "
            f"0x{actual_size:X} != original symbol size "
            f"0x{function_size:X}"
        )

    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())

    except (
        RuntimeError,
        subprocess.CalledProcessError,
    ) as exc:
        print(
            f"error: {exc}",
            file=sys.stderr,
        )
        raise SystemExit(1)
