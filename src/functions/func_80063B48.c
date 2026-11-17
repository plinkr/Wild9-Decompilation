// SPDX-License-Identifier: AGPL-3.0-or-later

#include "types.h"
#include "globals.h"

/**
 * Clears the first word of `count` 32-byte entries of D_80080F3C, starting at
 * entry `first`.
 */
void func_80063B48(u32 first, u32 count) {
    u32 i;
    u8* entry;

    for (i = 0; i < count; i++) {
        // Adding the offset to the base in its own statement keeps the
        // address in the base register, which frees the store for the loop
        // branch's delay slot.
        entry = D_80080F3C;
        entry += (i + first) * 0x20;
        *(s32*)entry = 0;
    }
}
