#!/usr/bin/env bash

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"

BINUTILS="$ROOT/tools/toolchain/binutils-2.42"

export PATH="$BINUTILS/usr/bin:$PATH"

export LD_LIBRARY_PATH="$BINUTILS/usr/lib/x86_64-linux-gnu:$BINUTILS/runtime/usr/lib/x86_64-linux-gnu${LD_LIBRARY_PATH:+:$LD_LIBRARY_PATH}"
