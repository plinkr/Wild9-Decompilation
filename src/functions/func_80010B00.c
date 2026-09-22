// SPDX-License-Identifier: AGPL-3.0-or-later
// https://decomp.me/scratch/ySqXz

#include "types.h"
#include "functions.h"
#include "globals.h"
#include "include_asm.h"
#include "decomp.h"

s32 func_80010B00(s32 arg0, void* arg1) {
    register u8* object asm("a2") = (u8*)arg0;
    register s32 difference asm("v0");
    register s32 other asm("v1");

    if (M2C_FIELD(arg1, u16*, 4) == 0) {
        goto success;
    }

    __asm__ volatile("" : "+r"(object));

#define CHECK_ABS_DIFF(offset1, offset2)                                       \
    difference = M2C_FIELD(object, s16*, offset1);                             \
    other = M2C_FIELD(object, s16*, offset2);                                  \
    difference -= other;                                                       \
    if (difference < 0)                                                        \
        difference = -difference;                                              \
    if (difference >= 2)                                                       \
        goto failure;

#define CHECK_MASK_DIFF(offset1, offset2)                                      \
    difference = M2C_FIELD(object, s16*, offset1);                             \
    other = M2C_FIELD(object, s16*, offset2);                                  \
    difference -= other;                                                       \
    difference &= 0xFFF;                                                       \
    if (difference >= 2)                                                       \
        goto failure;

    CHECK_ABS_DIFF(0x00, 0x18);
    CHECK_ABS_DIFF(0x02, 0x1A);
    CHECK_ABS_DIFF(0x04, 0x1C);
    CHECK_ABS_DIFF(0x06, 0x1E);
    CHECK_ABS_DIFF(0x08, 0x20);
    CHECK_ABS_DIFF(0x0A, 0x22);
    CHECK_MASK_DIFF(0x0E, 0x26);

    // Compare two masked differences and check their absolute difference.
    difference = M2C_FIELD(object, s16*, 0x10);
    other = M2C_FIELD(arg1, s16*, 8);
    difference -= other;

    other = M2C_FIELD(object, s16*, 0x28);
    other -= M2C_FIELD(arg1, s16*, 0x28);

    difference &= 0xFFF;
    other &= 0xFFF;
    difference -= other;
    if (difference < 0)
        difference = -difference;
    if (difference >= 2)
        goto failure;

    CHECK_MASK_DIFF(0x12, 0x2A);

#undef CHECK_ABS_DIFF
#undef CHECK_MASK_DIFF

success:
    return 1;

failure:
    return 0;
}
