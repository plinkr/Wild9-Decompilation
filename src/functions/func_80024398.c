// SPDX-License-Identifier: AGPL-3.0-or-later

#include "types.h"

// !FAKE: the ROM uses the trapping `add`, which GCC never emits for C
// arithmetic, so the sum is written as inline asm.
#define ADD(d, s) __asm__ volatile("add %0,%1,%2" : "=r"(d) : "r"(d), "r"(s))

// Adds three signed bytes of `a` and `b` pairwise and stores the sums scaled
// by 16; `n` is the first byte index of the group.
#define SUM_GROUP(n)                                                           \
    t0 = a[n];                                                                 \
    t1 = a[n + 1];                                                             \
    t2 = a[n + 2];                                                             \
    t3 = b[n];                                                                 \
    t4 = b[n + 1];                                                             \
    t5 = b[n + 2];                                                             \
    ADD(t0, t3);                                                               \
    ADD(t1, t4);                                                               \
    ADD(t2, t5);                                                               \
    t0 *= 16;                                                                  \
    t1 *= 16;                                                                  \
    t2 *= 16;                                                                  \
    dst[n - 1] = t0;                                                           \
    dst[n] = t1;                                                               \
    dst[n + 1] = t2

void func_80024398(s8* a, s8* b, s16* dst) {
    register s32 t0 asm("t0");
    register s32 t1 asm("t1");
    register s32 t2 asm("t2");
    register s32 t3 asm("t3");
    register s32 t4 asm("t4");
    register s32 t5 asm("t5");

    SUM_GROUP(1);
    SUM_GROUP(4);
    SUM_GROUP(7);
}
