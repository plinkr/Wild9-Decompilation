# Wild 9 Decompilation

Matching decompilation of Wild 9 for the Sony PlayStation 1, NTSC-U executable `SLUS_004.25`

## Overview

This project reconstructs the NTSC-U Wild 9 PlayStation 1 executable as matching C source and MIPS R3000A assembly. The primary goal is a byte-for-byte matching rebuild of the original executable (`SLUS_004.25`).

The codebase is structured around progressive decompilation. Matched functions are written as standalone C files under `src/functions/` and promoted into `src/main.c`, replacing the corresponding `INCLUDE_ASM` disassembly entries. Unmatched code remains as generated assembly slices. Each promoted function is independently compiled, linked, and matched against the original binary before being patched into the final rebuilt executable.

## Useful links

- [decomp.dev progress report](https://decomp.dev/plinkr/Wild9-Decompilation)
- [Wild 9 Recomp](https://github.com/plinkr/Wild9Recomp)

## Project status

This is a work-in-progress decompilation project for the original Wild 9 PlayStation 1 executable. Its purpose is to reconstruct the game's source code and produce a byte-for-byte matching rebuild of the original binary.

This repository is not a playable version of Wild 9. It contains the decompilation sources, build scripts, tools, and generated code required to reproduce the original executable from a legally obtained copy of the game. The original game executable and other copyrighted game assets are not included in this repository.

For a playable native PC recompilation of Wild 9, see [Wild 9 Recomp](https://github.com/plinkr/Wild9Recomp).

## Features

- Byte-for-byte matching rebuild against NTSC-U executable `SLUS_004.25`.
- Splat-based executable splitting and disassembly generation.
- GCC 2.8.0 PSX compiler toolchain with `maspsx` (ASPSX 2.77) assembly translation.
- Isolated GNU binutils 2.42 environment targeting `mipsel-linux-gnu`.
- Per-function standalone compilation, linking, and byte-exact verification.
- Automated function promotion workflow integrating matching C code into the main translation unit.
- Submodule integration for decompilation tools including `asm-differ`, `decomp-permuter`, `m2c`, `m2ctx`, `maspsx`, and `mipsmatch`.

## Requirements

The build and matching toolchain targets x86_64 Linux.

Host packages:

```bash
# Debian or Ubuntu
sudo apt install git make python3 python3-pip python3-venv curl binutils zstd file clang-format

# Arch Linux, Manjaro, or CachyOS
sudo pacman -S git make python python-pip curl binutils zstd file clang
```

Target game data:

A legally obtained original NTSC-U Wild 9 PlayStation executable must be placed at:

```text
iso/us/SLUS_004.25
```

Expected file identity:

```text
Size:    425984 bytes
SHA-1:   1dac75ee3a0ef5a62e025a85183076fa1a6cf824
SHA-256: ab280169ed52906589b8353a00c5cb4e9851da21d1023c98569de51958a44012
```

The original executable is not included in this repository.

## Setup

### 1. Clone the repository

Clone the repository with all Git submodules:

```bash
git clone --recursive https://github.com/plinkr/Wild9-Decompilation.git
cd Wild9-Decompilation
```

If the repository was cloned without `--recursive`, initialize the submodules:

```bash
make tools
```

### 2. Python environment

Create the Python virtual environment and install pinned dependencies:

```bash
make install
```

This installs `splat64` and `spimdisasm` into `.venv`.

### 3. Toolchain installation

The matching build requires GCC 2.8.0 PSX and GNU binutils 2.42 (`mipsel-linux-gnu`). Both are installed into `tools/toolchain/` without modifying system packages.

Install GCC 2.8.0 PSX:

```bash
mkdir -p tools/toolchain/gcc-2.8.0-psx
curl -fL "https://github.com/decompals/old-gcc/releases/download/0.17/gcc-2.8.0-psx.tar.gz" -o gcc-2.8.0-psx.tar.gz
echo "1a3c956fe8aea5ebdb251749d95de2c84f023530584d7bd663744b5ec24050b7  gcc-2.8.0-psx.tar.gz" | sha256sum -c -
tar -xzf gcc-2.8.0-psx.tar.gz -C tools/toolchain/gcc-2.8.0-psx --strip-components=1
rm gcc-2.8.0-psx.tar.gz
```

Install the private GNU binutils 2.42 environment:

```bash
mkdir -p tools/toolchain/distfiles tools/toolchain/binutils-2.42 tools/toolchain/binutils-2.42/runtime

curl -fL -o tools/toolchain/distfiles/binutils-mipsel-linux-gnu_2.42-2ubuntu1cross5_amd64.deb \
  https://archive.ubuntu.com/ubuntu/pool/universe/b/binutils-mipsen/binutils-mipsel-linux-gnu_2.42-2ubuntu1cross5_amd64.deb

curl -fL -o tools/toolchain/distfiles/libsframe1_2.42_amd64.deb \
  https://archive.ubuntu.com/ubuntu/pool/main/b/binutils/libsframe1_2.42-4ubuntu2.10_amd64.deb

ar x tools/toolchain/distfiles/binutils-mipsel-linux-gnu_2.42-2ubuntu1cross5_amd64.deb --output tools/toolchain/binutils-2.42
tar --zstd -xf tools/toolchain/binutils-2.42/data.tar.zst -C tools/toolchain/binutils-2.42

ar x tools/toolchain/distfiles/libsframe1_2.42_amd64.deb --output tools/toolchain/binutils-2.42/runtime
tar --zstd -xf tools/toolchain/binutils-2.42/runtime/data.tar.zst -C tools/toolchain/binutils-2.42/runtime
```

See `docs/TOOLCHAIN.md` for additional details on toolchain verification.

### 4. Load the environment

Load the private binutils environment in every shell session used for building:

```bash
source scripts/binutils-env.sh
```

### 5. Install the original executable

Wild 9 (NTSC-U) ships as `SLUS_004.25`. You need this executable in `iso/us/` before building.

#### Extract it from your own Wild 9 disc image

If you have a Redump-style dump of Wild 9 (`.cue` + `.bin`, or a bare `.bin`), use the helper script in this repo:

```bash
python scripts/extract_psx_exe.py "/path/to/Wild 9 (USA).cue"
```

The script reads the filesystem inside the dump, follows `SYSTEM.CNF` to the boot executable, and writes `SLUS_004.25` to the current directory. Then move it into place:

```bash
mkdir -p iso/us
mv SLUS_004.25 iso/us/SLUS_004.25
```

You can also pass the output path directly:

```bash
python scripts/extract_psx_exe.py "/path/to/Wild 9 (USA).bin" iso/us/SLUS_004.25
```

#### Or copy it manually

If you already have `SLUS_004.25` extracted (for example from DuckStation's disc browser), just place it at:

```bash
mkdir -p iso/us
cp /path/to/SLUS_004.25 iso/us/SLUS_004.25
```

Either way, the final layout must be:

```text
iso/us/SLUS_004.25
```

### 6. Verify the toolchain

Verify the installed tools:

```bash
make versions
mipsel-linux-gnu-as --version
mipsel-linux-gnu-ld --version
mipsel-linux-gnu-objcopy --version
```

All binutils utilities must report version 2.42.

## Build

Generate the Splat disassembly output:

```bash
make split
```

Build and verify the baseline all-assembly reference:

```bash
make original-verify
```

Build the target executable:

```bash
make build
```

Verify that the built executable matches the original:

```bash
make verify
```

The build process starts from the byte-exact reference and replaces promoted functions defined in `src/main.c`. Each promoted function is matched independently before its bytes are patched into the final executable.

## Matching

Each decompiled function lives in its own file under:

```text
src/functions/func_XXXXXXXX.c
```

To build and compare a standalone function against the original binary:

```bash
make match FUNCTION=func_XXXXXXXX
```

For example:

```bash
make match FUNCTION=func_800101A4
```

A successful match prints:

```text
func_800101A4: MATCH
```

The standalone matching pipeline is:

```text
src/functions/func_XXXXXXXX.c
    -> C preprocessor (CPP)
    -> GCC 2.8.0 PSX compiler
    -> scripts/prepare_function_asm.py (small-data handling)
    -> maspsx (ASPSX 2.77 translation)
    -> GNU assembler 2.42 (mipsel-linux-gnu-as)
    -> scripts/link_function.py (standalone link at original address)
    -> scripts/match_function.py (byte comparison against original binary)
```

The project does not modify the `tools/maspsx` submodule. `scripts/prepare_function_asm.py` handles small-data preparation before invoking maspsx.

## Development Workflow

### 1. Decompiling a function

Find an unpromoted function in `src/main.c`. Unpromoted functions appear as:

```c
INCLUDE_ASM("asm/nonmatchings/main", func_XXXXXXXX);
```

The disassembled assembly generated by `make split` is located at:

```text
asm/nonmatchings/main/func_XXXXXXXX.s
```

Create a standalone C source file:

```bash
$EDITOR src/functions/func_XXXXXXXX.c
```

Write the C implementation using fixed-width types from `include/types.h` and shared declarations from `include/functions.h`, `include/globals.h`, and `include/decomp.h`.

### 2. Testing and matching

Compile and compare the function:

```bash
make match FUNCTION=func_XXXXXXXX
```

Iterate on the C code until `make match` reports `MATCH`. Decompilation helper submodules under `tools/` (such as `asm-differ` or `decomp-permuter`) can be used to analyze differences.

### 3. Promoting a matched function

Once `make match` succeeds, promote the function:

```bash
make promote FUNCTION=func_XXXXXXXX
```

`make promote` performs the following steps:
1. Verifies the standalone match with `make match`.
2. Replaces the `INCLUDE_ASM("asm/nonmatchings/main", func_XXXXXXXX);` line in `src/main.c` with `#include "functions/func_XXXXXXXX.c"`.
3. Rebuilds the executable with `make build`.
4. Runs `make verify` to ensure the entire binary matches byte-for-byte.
5. If verification fails, it automatically restores `src/main.c` from backup.

### 4. Formatting

Format C source and header files:

```bash
make format
```

This applies `.clang-format` rules and verifies that all C and header files start with the project SPDX license identifier:

```c
// SPDX-License-Identifier: AGPL-3.0-or-later
```

Do not alter code purely for formatting if the change modifies the generated assembly. Refer to `docs/STYLE.md` for coding and formatting conventions.

## Project Structure

```text
src/
  main.c
      Main translation unit containing promoted C includes and remaining INCLUDE_ASM macros.
  functions/
      Standalone C source files, one per decompiled function.

include/
  types.h
      Fixed-width integer types (u8, s8, u16, s16, u32, s32, bool).
  functions.h
      Shared function declarations.
  globals.h
      Shared game global variable declarations.
  decomp.h
      Decompilation helpers, hardware structures, and macros.
  include_asm.h
      INCLUDE_ASM and INCLUDE_RODATA macro definitions.
  macro.inc
      Assembler macros.
  labels.inc
      Assembler label declarations.
  gte_macros.inc
      PlayStation Geometry Transformation Engine (GTE) assembly macros.

config/slus_004.25/
  splat.yaml
      Splat disassembly and section split configuration.
  toolchain.json
      Compiler and assembler flags and tool versions.
  SLUS_004.25.sha1
      SHA-1 checksum of the original executable.
  SLUS_004.25.sha256
      SHA-256 checksum of the original executable.

symbols/
  slus_004.25.txt
      Hardware register mappings, BIOS symbols, and known addresses.

scripts/
  binutils-env.sh
      Sets PATH and LD_LIBRARY_PATH for the private binutils 2.42 environment.
  match_function.py
      Compares standalone function binary against the original executable.
  link_function.py
      Links a standalone function object at its original address.
  prepare_function_asm.py
      Prepares standalone GCC assembly output before passing to maspsx.
  prepare_main_asm.py
      Prepares main translation unit assembly output.
  promote_function.py
      Replaces INCLUDE_ASM entries with C includes in src/main.c.
  normalize_splat_config.py
      Normalizes generated Splat split configuration.
  inspect_psx_exe.py
      Parses and displays PlayStation executable header information.

docs/
  STYLE.md
      C style guide, naming conventions, and matching guidelines.
  TOOLCHAIN.md
      Detailed toolchain setup instructions and package references.
  REPOSITORY.md
      Repository clean-room reverse engineering policy.

tools/
  Git submodules for decompilation tooling and local toolchain files.
```

Generated assembly (`asm/`), linker scripts, object files, and build outputs (`build/`) are ignored by Git.

## Useful Commands

```bash
make help                           # Show available Makefile targets
make versions                       # Print Python, splat, and spimdisasm versions
make info                           # Display PS-X EXE header fields
make fingerprint                    # Record SHA-1 and SHA-256 of the target binary
make split                          # Run Splat to disassemble binary sections
make original-verify                # Build and verify the baseline assembly reference
make build                          # Build the final executable with promoted functions
make verify                         # Compare build/SLUS_004.25 with the original
make match FUNCTION=func_XXXXXXXX   # Build and match a single function
make promote FUNCTION=func_XXXXXXXX # Promote a matched function in src/main.c
make format                         # Format C/header files with clang-format
make clean                          # Remove build artifacts
make distclean                      # Remove build artifacts and Python virtualenv
```

## Contributing

- Keep one decompiled function per file under `src/functions/func_XXXXXXXX.c`.
- Keep promoted functions in original address order in `src/main.c`.
- Follow the conventions in `docs/STYLE.md`.
- Before submitting a pull request, run:
  ```bash
  source scripts/binutils-env.sh
  make format
  make verify
  ```
- Do not commit original game executables, disc images, extracted assets, generated assembly, object files, or other build artifacts.

## License

Project source code, scripts, configuration, and documentation are licensed under the GNU Affero General Public License version 3. See `LICENSE.md`.

The Wild 9 executable, disc data, artwork, audio, and other original game assets are copyrighted by their respective rights holders and are not licensed by this project.
