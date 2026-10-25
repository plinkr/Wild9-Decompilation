// SPDX-License-Identifier: AGPL-3.0-or-later

#include "types.h"

// Scales nine signed bytes (src[1..9]) by 32 into halfwords. The ROM reads
// like hand-written code: fixed $t0-$t8 registers and shifts interleaved with
// stores in groups of three.
// !FAKE: the pinned registers and the empty asm barriers reproduce that
// layout; without the barriers GCC hoists all nine shifts above the stores.
void func_80024328(s8* src, s32 arg1, s16* dst) {
    register s32 t0 asm("t0") = src[1];
    register s32 t1 asm("t1") = src[2];
    register s32 t2 asm("t2") = src[3];
    register s32 t3 asm("t3") = src[4];
    register s32 t4 asm("t4") = src[5];
    register s32 t5 asm("t5") = src[6];
    register s32 t6 asm("t6") = src[7];
    register s32 t7 asm("t7") = src[8];
    register s32 t8 asm("t8") = src[9];

    t0 *= 32;
    t1 *= 32;
    t2 *= 32;
    __asm__ volatile("");
    dst[0] = t0;
    dst[1] = t1;
    dst[2] = t2;
    __asm__ volatile("");
    t3 *= 32;
    t4 *= 32;
    t5 *= 32;
    __asm__ volatile("");
    dst[4] = t4;
    dst[5] = t5;
    dst[3] = t3;
    __asm__ volatile("");
    t6 *= 32;
    t7 *= 32;
    t8 *= 32;
    __asm__ volatile("");
    dst[6] = t6;
    dst[7] = t7;
    dst[8] = t8;
}
