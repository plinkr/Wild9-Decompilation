// SPDX-License-Identifier: AGPL-3.0-or-later

#include "types.h"
#include "globals.h"

/**
 * Busy-waits until bit 1 of the halfword at +4 of D_80076490 is set.
 */
void func_800659B4(void) {
    u8* p = D_80076490;

    while (!(*(volatile u16*)(p + 4) & 2)) {
    }
}
