# Wild 9 Decompilation

Matching decompilation of `Wild 9` for the Sony PlayStation 1 (NTSC-U, SLUS-00425)

## Overview

This project reconstructs readable C source code that can reproduce the
original PlayStation executable at the machine code level. The target is the
NTSC-U executable identified as `SLUS_004.25`.

The project is in an early decompilation stage. The repository contains the
Splat configuration, analysis scripts, disassembly tooling, source layout, and
matching helpers. The current matching toolchain is GCC 2.8.0 PSX with GNU
binutils 2.42. The selected versions and flags are recorded in
`config/slus_004.25/toolchain.json`.

## Features

- PlayStation 1 MIPS R3000A executable analysis.
- Splat based executable splitting and disassembly.
- GCC 2.8.0 PSX matching through `decompals/old-gcc` release `0.17`.
- Private Ubuntu Noble GNU binutils 2.42 installation for
  `mipsel-linux-gnu`.
- ASPSX compatible assembly translation through `maspsx`.
- Function matching against bytes extracted from the original executable.
- Assembly comparison, decompilation, context generation, and permutation
  tooling provided through Git submodules.

## Repository policy

This is a clean room reverse engineering project:

- The repository does not contain original game binaries, disc images,
  copyrighted game assets, or proprietary PlayStation SDK headers.
- Contributors must provide their own legally acquired copy of the game.
- Generated assembly, intermediate objects, binary dumps, and matching output
  remain in ignored directories such as `iso/`, `asm/`, and `build/`.
- Fingerprint files committed under `config/slus_004.25/` contain hashes and
  toolchain configuration, not original game data.

## Requirements

### Host environment

The local toolchain packages are Ubuntu `amd64` packages, so the documented
setup requires an x86_64 Linux host.

- Linux x86_64
- Git
- GNU Make
- Python 3 with `python3-pip` and `python3-venv`
- `curl`
- GNU `ar`
- `tar` with zstd support
- `sha1sum`, `sha256sum`, `timeout`, `cmp`, and other standard Unix utilities

Example package installation commands:

```bash
# Debian or Ubuntu
sudo apt install git make python3 python3-pip python3-venv curl binutils zstd file

# Arch Linux, Manjaro, CachyOS
sudo pacman -S git make python python-pip curl binutils zstd file
```

### Original game data

An original NTSC-U Wild 9 disc or executable extraction is required. Place the
executable at:

```text
iso/us/SLUS_004.25
```

The expected executable metadata is:

```text
Size:    425984 bytes (0x68000)
SHA 1:   1dac75ee3a0ef5a62e025a85183076fa1a6cf824
SHA 256: ab280169ed52906589b8353a00c5cb4e9851da21d1023c98569de51958a44012
```

### Python dependencies

The pinned Python dependencies are installed into the local `.venv` by the
Makefile:

- `splat64[mips]==0.50.0`
- `spimdisasm==1.42.4`

## Setup

Clone the repository and initialize its tooling submodules:

```bash
git clone --recursive https://github.com/plinkr/Wild9-Decompilation.git
cd Wild9-Decompilation
```

If the repository was cloned without submodules, initialize them with:

```bash
make tools
```

Place the legally obtained executable in the expected location:

```bash
mkdir -p iso/us
cp /path/to/SLUS_004.25 iso/us/SLUS_004.25
```

Create the Python environment and install the pinned analysis dependencies:

```bash
make install
```

Install the exact compiler and assembler toolchain used for matching by
following [docs/TOOLCHAIN.md](docs/TOOLCHAIN.md). That document covers:

- GCC 2.8.0 PSX from `decompals/old-gcc`, release `0.17`.
- SHA 256 verification of `gcc-2.8.0-psx.tar.gz`.
- Extraction to `tools/toolchain/gcc-2.8.0-psx/`.
- Ubuntu Noble `binutils-mipsel-linux-gnu` version 2.42.
- The matching `libsframe1` runtime dependency.
- Local extraction without modifying the system installation.
- Activation through `scripts/binutils-env.sh`.

The compiler archive checksum is:

```text
1a3c956fe8aea5ebdb251749d95de2c84f023530584d7bd663744b5ec24050b7
```

After installing binutils, load the private runtime environment in every new
shell before invoking assembler, linker, or matching commands:

```bash
source scripts/binutils-env.sh
```

Verify the installed tools:

```bash
mipsel-linux-gnu-as --version
mipsel-linux-gnu-ld --version
mipsel-linux-gnu-objcopy --version
```

The GCC version output begins with `GNU C version 2.8.0 (mips-sony-psx)`.
The binutils commands must report version 2.42. The GCC version command uses a
timeout because this historical `cc1` build can print its version and not exit
by itself.

## Build and analysis commands

Check the Python and analysis tool versions:

```bash
make versions
make info
make fingerprint
```

Generate the initial Splat configuration and split the executable:

```bash
make create-config
make split
```

Review the generated configuration and symbol files before committing them:

```text
config/slus_004.25/splat.yaml
symbols/slus_004.25.txt
symbols/slus_004.25.relocs.txt
```

Splat writes generated disassembly under `asm/`, which is intentionally not
tracked by Git.

## Matching workflow

The matching pipeline is:

```text
C source
  -> C preprocessor
  -> GCC 2.8.0 PSX cc1
  -> maspsx ASPSX 2.77 translation
  -> GNU assembler 2.42
  -> relocatable MIPS object
  -> optional GNU linker step
  -> byte comparison with the original executable
```

The selected compiler flags are:

```text
-quiet -O2 -G0 -mips1 -mcpu=3000 -mgas -msoft-float -fgnu-linker -g0
```

The selected `maspsx` profile is ASPSX 2.77 without `--expand-div`. GNU
assembler uses:

```text
-EL -march=r3000 -mtune=r3000 -no-pad-sections -O1 -G0
```

These values are recorded in `config/slus_004.25/toolchain.json` and should
be treated as the project defaults.

Before matching, source the binutils environment:

```bash
source scripts/binutils-env.sh
```

## Tooling submodules

The repository tracks these open source tools as submodules:

- `asm-differ`: Interactive assembly comparison.
- `decomp-permuter`: Source permutation search for matching functions.
- `m2c`: MIPS assembly to C decompilation assistant.
- `m2ctx`: Context generator for macros and typedefs.
- `maspsx`: GCC to Sony ASPSX assembly translator.
- `mipsmatch`: Function matching and coverage reporting.
- `psx_psyq_signatures`: Psy Q library signatures.

## Development

Follow [docs/STYLE.md](docs/STYLE.md) for C naming, formatting, types, and
function ordering. C functions must remain in the same order as the original
assembly when matching layout sensitive code.

Keep original game data and generated output outside version control. Do not
commit disc images, executables, extracted assets, proprietary SDK code,
generated assembly, object files, or matching output.

When changing compiler or assembler behavior, update the relevant configuration
and document the reason. Toolchain changes must be validated against frozen
preprocessed input and more than one matching function before being treated as
the project default.

## Contributing

Before submitting changes:

1. Follow `docs/STYLE.md` for source changes.
2. Preserve the clean room repository policy.
3. Verify Splat configuration and symbol address changes.
4. Source `scripts/binutils-env.sh` when running matching or assembler tools.
5. Include the relevant command and result when a toolchain or matching change
   affects generated output.

## License

The original source, scripts, and configuration in this repository are
licensed under the GNU Affero General Public License version 3. See
`LICENSE.md`.

The Wild 9 name, executable, disc data, and game assets are copyrighted by
their respective rights holders. This project is an unofficial clean room
reverse engineering effort and is not affiliated with or endorsed by Shiny
Entertainment, Interplay Productions, or Sony Interactive Entertainment.
