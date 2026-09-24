// SPDX-License-Identifier: AGPL-3.0-or-later
// https://decomp.me/scratch/xKTeB

#include "types.h"
#include "globals.h"

void func_80010000(void) {
    u8* base;
    s32 temp_v0;
    s32 temp_v1;

    base = (u8*)&D_8007B350;

    if (M2C_FIELD(base, s32*, 0xF0) != 0) {
        temp_v1 = D_8007C78C;
        __asm__ volatile("" : "+r"(temp_v1));

        M2C_FIELD(base, s32*, 0x3C) = 0x3C;
        if (temp_v1 != 0) {
            M2C_FIELD(base, s32*, 0x40) = 0x384;
            return;
        }

        temp_v0 = M2C_FIELD(base, s32*, 0x40) - 1;
        M2C_FIELD(base, s32*, 0x40) = temp_v0;
        if (temp_v0 <= 0) {
            M2C_FIELD(base, s32*, 0x110) = 1;
            D_8007754C = 2;
        }
    } else {
        M2C_FIELD(base, s32*, 0x40) = 0x384;

        if ((D_8007C78C & 0x30000000) ||
            (((D_8007C78C & 0x3000) == 0x3000) &&
             (M2C_FIELD(base, s32*, 0x3C) < 0x3C))) {
            if (M2C_FIELD(base, s32*, 0x3C) > 0) {
                M2C_FIELD(base, s32*, 0x3C) = M2C_FIELD(base, s32*, 0x3C) - 1;
                return;
            }
            return;
        }

        D_8007B38C = 0x3C;
    }
}
