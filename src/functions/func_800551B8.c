// SPDX-License-Identifier: AGPL-3.0-or-later

#include "types.h"
#include "functions.h"

s32 func_800551B8(s32 arg0) {
    // !FAKE: pinning `delta` to $s0 keeps the ROM's second copy to $v0 after
    // the wrap-around; otherwise GCC folds it into the addition.
    register s32 delta asm("s0") = (func_80057340(0xF2000001) << 6) - arg0;

    if (delta < 0) {
        delta += 0x400000;
    }
    return delta;
}
