"""Layout facts about the main executable shared by the build scripts."""

from __future__ import annotations

# First function of the Sony library: the libapi BIOS call stubs. Everything
# before it is game code (the FMV player at func_80056740..func_8005706C still
# calls game functions); everything from it on is library code (libapi, libetc,
# libc, libgpu, libgte, libspu, libcd, libpress, ...).
SDK_START = 0x800571C4


def function_address(name: str) -> int:
    """Return the address of a `func_XXXXXXXX` symbol."""
    return int(name.removeprefix("func_"), 16)


def is_sdk_function(name: str) -> bool:
    return function_address(name) >= SDK_START
