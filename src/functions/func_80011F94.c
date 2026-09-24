// SPDX-License-Identifier: AGPL-3.0-or-later
// https://decomp.me/scratch/BggKS

#include "types.h"
#include "functions.h"
#include "globals.h"

void func_80011F94(void) {
    s32* base = D_8007B350;
    register s32 flags asm("v0");
    s32 original;

    original = base[0x308 / 4];
    if (original & 2) {
        flags = original & ~2;
        base[0x308 / 4] = flags;
        if (flags == 0) {
            func_8004EF08(base);
        }
    }
}
