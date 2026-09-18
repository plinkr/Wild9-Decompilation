# Wild 9 Decompilation

Matching decompilation of Wild 9 for the Sony PlayStation 1 (NTSC-U, SLUS-00425).

## Overview

This project aims to reconstruct readable C source code that compiles to match
the original PlayStation 1 executable (SLUS_004.25) byte-for-byte.

The project is in its early stages. Initial repository structure, binary analysis
scripts, disassembly and splitting configuration via Splat, and decompilation
tool submodules are in place. Selection of the matching C compiler toolchain and
the build system for recompilation are in progress.

## Repository Policy

This project strictly adheres to clean-room reverse engineering practices:

- The repository does not contain original game binaries, disc images,
  copyrighted game assets, or proprietary PlayStation SDK headers.
- Contributors must provide their own legally acquired copy of the game.
- Generated assembly, intermediate objects, and binary dumps must remain
  in untracked directories (such as iso/, asm/, and build/).
- Fingerprint files committed to config/slus_004.25/ contain only
  cryptographic hashes (SHA-1, SHA-256).

## Requirements

### Host Environment

- Linux (x86_64)
- Git
- GNU Make
- Python 3 (with python3-pip and python3-venv)
- Standard Unix utilities (file, sha1sum, sha256sum)

Example package installation commands:

- Debian / Ubuntu:
  ```bash
  sudo apt install git make python3 python3-pip python3-venv file
  ```
- Arch Linux:
  ```bash
  sudo pacman -S git make python python-pip base-devel file
  ```
- Fedora:
  ```bash
  sudo dnf install git make python3 python3-pip file
  ```

### Target Game Data

An original NTSC-U Wild 9 game disc is required to extract the executable:

- Path: iso/us/SLUS_004.25
- Size: 425984 bytes (0x68000)
- SHA-1: 1dac75ee3a0ef5a62e025a85183076fa1a6cf824
- SHA-256: ab280169ed52906589b8353a00c5cb4e9851da21d1023c98569de51958a44012

### Python Dependencies

Pinned dependencies are installed automatically into a local .venv by the
Makefile:

- splat64[mips]==0.50.0
- spimdisasm==1.42.4

## Setup

1. Clone the repository and initialize submodules:

   ```bash
   git clone --recursive https://github.com/plinkr/Wild9-Decompilation
   cd Wild9-Decompilation
   ```

   If already cloned without --recursive:

   ```bash
   make tools
   ```

2. Place the original NTSC-U PlayStation executable in the expected directory:

   ```bash
   mkdir -p iso/us
   cp /path/to/SLUS_004.25 iso/us/SLUS_004.25
   ```

3. Create the local Python virtual environment and install dependencies:

   ```bash
   make install
   ```

4. Verify tool versions and executable integrity:

   ```bash
   make versions
   make info
   make fingerprint
   ```

## Usage

The project uses GNU Make to drive setup, analysis, and splitting tasks.

| Target               | Description                                              |
| -------------------- | -------------------------------------------------------- |
| make help            | List available Makefile targets                          |
| make venv            | Create local Python virtual environment (.venv)          |
| make install         | Install pinned Python dependencies into .venv            |
| make tools           | Initialize and update Git submodules                     |
| make versions        | Display versions of Python, splat64, and spimdisasm      |
| make verify-input    | Check that iso/us/SLUS_004.25 exists locally             |
| make info            | Parse and display PS-X EXE header fields                 |
| make fingerprint     | Record SHA-1 and SHA-256 hashes to config/slus_004.25/   |
| make create-config   | Generate and normalize the Splat split configuration     |
| make split           | Disassemble and split binary into assembly sections      |
| make clean           | Remove generated Python virtual environment (.venv)      |

## Splitting the Binary

To generate the initial Splat configuration and disassemble the target
executable:

```bash
make create-config
make split
```

Review config/slus_004.25/splat.yaml, symbols/slus_004.25.txt, and
symbols/slus_004.25.relocs.txt. Splat will generate raw disassembly under
asm/, which is ignored by version control.

## Matching and Tooling

Matching decompilation compares the compiled output of reconstructed C
functions against the original MIPS R3000A assembly until a byte-level match is
achieved.

The repository tracks common decompilation tools as submodules in tools/:

- asm-differ: Interactive visual diff utility for assembly comparison.
- decomp-permuter: Automated permutation tool for matching tough functions.
- m2c: MIPS assembly to C decompilation assistant.
- m2ctx: Context generator script for macro and typedef expansion.
- maspsx: Modern GCC to Sony ASPSX assembly translator.
- mipsmatch: Function matching and coverage report generator.
- psx_psyq_signatures: Psy-Q library signatures for identifying SDK functions.

As the project is in early development, compiler selection and matching diff
targets will be configured once the Psy-Q SDK version is determined.

## Development Conventions

Refer to docs/STYLE.md for the complete style guide.

- Types: Use fixed-width types from types.h (u8, s8, u16, s16, u32,
  s32, bool) instead of standard C types (char, short, int).
- Formatting: 4-space indentation, no tabs, 80-column margin limit, opening
  braces on the same line (clang-format compatible).
- Naming:
  - Local variables: camelCase
  - Global variables: g_PascalCase
  - Static variables: s_PascalCase
  - Struct types: PascalCase, struct members: camelCase
  - Enum types: PascalCase, enum values: SCREAMING_SNAKE_CASE
  - Macros and constants: SCREAMING_SNAKE_CASE
  - Functions: PascalCase
  - Source files: snake_case
- Function Order: C source files must maintain the exact function order of the
  original executable to ensure matching layout during linking.

## Contributing

Contributions are welcome. Prior to submitting changes:

1. Ensure code adheres to docs/STYLE.md and project formatting conventions.
2. Maintain clean-room standards: never submit original game assets or
   proprietary SDK code.
3. Test Splat configurations and verify that symbol addresses remain consistent.

## License

The code and tooling configurations in this repository are licensed under the
GNU Affero General Public License v3 (AGPL-3.0). See LICENSE.md for details.

Wild 9 is copyright (C) 1998 Shiny Entertainment, Inc. / Interplay Productions.
This project is an unofficial clean-room reverse engineering effort and is not
affiliated with or endorsed by Shiny Entertainment, Interplay, or Sony
Interactive Entertainment.
