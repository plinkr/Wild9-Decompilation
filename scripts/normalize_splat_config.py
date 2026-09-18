#!/usr/bin/env python3
import re
import sys
from pathlib import Path


def main() -> int:
    if len(sys.argv) != 6:
        print(
            f"usage: {sys.argv[0]} INPUT_YAML OUTPUT_YAML SYMBOLS RELOCS TARGET",
            file=sys.stderr,
        )
        return 2

    input_path, output_path, symbols, relocs, target = map(Path, sys.argv[1:])
    text = input_path.read_text(encoding="utf-8")
    basename = target.name.lower()

    replacements = {
        r"^  target_path: .*$": f"  target_path: {target}",
        r"^  elf_path: .*$": f"  elf_path: build/{basename}.elf",
        r"^  base_path: .*$": "  base_path: ../..",
        r"^  ld_script_path: .*$": f"  ld_script_path: linker/{basename}.ld",
    }

    for pattern, replacement in replacements.items():
        text, count = re.subn(pattern, replacement, text, count=1, flags=re.MULTILINE)
        if count != 1:
            raise SystemExit(f"could not normalize expected YAML field: {pattern}")

    text = text.replace("  # asm_path: asm", "  asm_path: asm", 1)
    text = text.replace("  # src_path: src", "  src_path: src", 1)
    text = text.replace("  # build_path: build", "  build_path: build", 1)
    text = text.replace("    - symbol_addrs.txt", f"    - {symbols}", 1)
    text = text.replace("    - reloc_addrs.txt", f"    - {relocs}", 1)

    output_path.write_text(text, encoding="utf-8", newline="\n")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
