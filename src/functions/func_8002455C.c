// SPDX-License-Identifier: AGPL-3.0-or-later

#include "types.h"

// !FAKE: the ROM uses $t0-$t2 (like its hand-written neighbours
// func_80024328 / func_80024398); GCC picks $v0/$v1/$a0 unless pinned.
void func_8002455C(s16* arg0, s32 arg1, s32* arg2) {
    register s32 x asm("t0") = arg0[5];
    register s32 y asm("t1") = arg0[6];
    register s32 z asm("t2") = arg0[7];

    arg2[5] = x;
    arg2[6] = y;
    arg2[7] = z;
}
