# Wild 9 toolchain setup

Wild 9 uses the toolchain recorded in `config/slus_004.25/toolchain.json`.
The compiler is GCC 2.8.0 PSX and the assembler and linker are GNU binutils
2.42. Follow the GCC section first, then install the private binutils build.

## GCC 2.8.0 PSX

The project uses the PSX build of GCC 2.8.0 distributed by
`decompals/old-gcc`, release `0.17`. This is a precompiled historical build;
the repository does not require rebuilding GCC from source.

Run this script from the repository root:

```bash
set -e

URL="https://github.com/decompals/old-gcc/releases/download/0.17/gcc-2.8.0-psx.tar.gz"
SHA256="1a3c956fe8aea5ebdb251749d95de2c84f023530584d7bd663744b5ec24050b7"

TMP_DIR="$(mktemp -d)"
ARCHIVE="$TMP_DIR/gcc-2.8.0-psx.tar.gz"
DEST="$(pwd)/tools/toolchain/gcc-2.8.0-psx"

trap 'rm -rf "$TMP_DIR"' EXIT

curl -fL "$URL" -o "$ARCHIVE"

echo "$SHA256  $ARCHIVE" | sha256sum -c -

rm -rf "$DEST"
mkdir -p "$DEST"

tar -xzf "$ARCHIVE" -C "$DEST" --strip-components=1

test -x "$DEST/cc1"

echo
echo "GCC 2.8.0 PSX installed correctly:"
echo "  $DEST/cc1"
```

Verify the installed compiler:

```bash
test -x tools/toolchain/gcc-2.8.0-psx/cc1
timeout 2s tools/toolchain/gcc-2.8.0-psx/cc1 -version
```

The timeout is intentional. This historical build can print its version and
then fail to terminate by itself. The output should begin with:

```text
GNU C version 2.8.0 (mips-sony-psx) compiled by GNU C version 9.4.0.
```

The installed archive `gcc-2.8.0-psx.tar.gz` must have this SHA-256 checksum:

```text
1a3c956fe8aea5ebdb251749d95de2c84f023530584d7bd663744b5ec24050b7
```

The matching pipeline invokes the GCC driver at `tools/toolchain/gcc-2.8.0-psx/gcc`, which uses the bundled GCC 2.8.0 PSX compiler components.

The archive is downloaded from the `0.17` release of `decompals/old-gcc`:

```text
https://github.com/decompals/old-gcc/releases/download/0.17/gcc-2.8.0-psx.tar.gz
```

## Binutils 2.42 setup

This section covers the private GNU binutils installation required by the
project.

The project uses the Ubuntu Noble `amd64` package
`binutils-mipsel-linux-gnu_2.42-2ubuntu1cross5_amd64.deb`. It is extracted
inside the repository instead of being installed into the host system. This
is useful on Manjaro and Arch Linux systems where the available binutils or
runtime libraries do not have the required versions.

## Requirements

Install these host utilities with the package manager for your system:

- `curl`
- `ar` (provided by GNU binutils)
- `tar` with zstd support

The packages below are Ubuntu `amd64` packages. The setup therefore requires
an x86_64 Linux host.

## Download the packages

Run these commands from the repository root. The binutils URL is an Ubuntu
archive mirror path listed on the Ubuntu package download page. The mirror
can be changed if necessary, but the package version and filename must stay
the same.

```bash
mkdir -p tools/toolchain/distfiles

curl -L --fail \
  -o tools/toolchain/distfiles/binutils-mipsel-linux-gnu_2.42-2ubuntu1cross5_amd64.deb \
  https://archive.ubuntu.com/ubuntu/pool/universe/b/binutils-mipsen/binutils-mipsel-linux-gnu_2.42-2ubuntu1cross5_amd64.deb

curl -L --fail \
  -o tools/toolchain/distfiles/libsframe1_2.42_amd64.deb \
  https://archive.ubuntu.com/ubuntu/pool/main/b/binutils/libsframe1_2.42-4ubuntu2.10_amd64.deb
```

The expected package versions are:

```text
binutils-mipsel-linux-gnu 2.42-2ubuntu1cross5
libsframe1 2.42-4ubuntu2.10
```

The first package is available from the Ubuntu package page:

```text
https://packages.ubuntu.com/noble/amd64/binutils-mipsel-linux-gnu/download
```

## Extract binutils

Do not install either package with the system package manager. Extract both
packages into the repository-local toolchain directory:

```bash
rm -rf tools/toolchain/binutils-2.42
mkdir -p tools/toolchain/binutils-2.42

ar x \
  tools/toolchain/distfiles/binutils-mipsel-linux-gnu_2.42-2ubuntu1cross5_amd64.deb \
  --output tools/toolchain/binutils-2.42

tar --zstd \
  -xf tools/toolchain/binutils-2.42/data.tar.zst \
  -C tools/toolchain/binutils-2.42
```

Extract `libsframe1` into the runtime directory used by the environment
script:

```bash
mkdir -p tools/toolchain/binutils-2.42/runtime

ar x \
  tools/toolchain/distfiles/libsframe1_2.42_amd64.deb \
  --output tools/toolchain/binutils-2.42/runtime

tar --zstd \
  -xf tools/toolchain/binutils-2.42/runtime/data.tar.zst \
  -C tools/toolchain/binutils-2.42/runtime
```

After extraction, the important paths are:

```text
tools/toolchain/binutils-2.42/usr/bin/mipsel-linux-gnu-as
tools/toolchain/binutils-2.42/usr/bin/mipsel-linux-gnu-ld
tools/toolchain/binutils-2.42/usr/bin/mipsel-linux-gnu-objcopy
tools/toolchain/binutils-2.42/usr/lib/x86_64-linux-gnu/
tools/toolchain/binutils-2.42/runtime/usr/lib/x86_64-linux-gnu/libsframe.so.1
```

## Load the project environment

Before building or running matching scripts, source the environment script
from the repository root:

```bash
source scripts/binutils-env.sh
```

The script prepends the private binutils directory to `PATH` and adds both
private library directories to `LD_LIBRARY_PATH`. This ensures that the
project uses binutils 2.42 and the matching `libsframe.so.1` instead of host
versions.

Verify the selected tools:

```bash
mipsel-linux-gnu-as --version
mipsel-linux-gnu-ld --version
mipsel-linux-gnu-objcopy --version
```

Each command must report GNU binutils version 2.42. If a command cannot load
its libraries, source `scripts/binutils-env.sh` again in the current shell
after completing the extraction.

The environment is shell-local. Run `source scripts/binutils-env.sh` again
whenever a new shell is opened.
