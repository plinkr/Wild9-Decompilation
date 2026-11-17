// SPDX-License-Identifier: AGPL-3.0-or-later

#include "types.h"
#include "globals.h"

/**
 * Returns whether the timeout armed by func_80067748 has expired: the ticks of
 * root counter 1 (0x1F801120) since D_8007B198, compensating one wrap at the
 * target value (0x1F801128, or 0x10000 when it is 0), compared against
 * D_8007F6FC. Without the clock-source bit 0x200 of the mode register
 * (0x1F801124) the elapsed value is divided by 8.
 */
s32 func_80067768(void) {
    u32 now = *(volatile u16*)0x1F801120;
    u32 elapsed;
    // !FAKE: pinning `limit` to $v1 moves `now` to $a0 like the original.
    register u32 limit asm("v1");

    if (now < D_8007B198) {
        if (*(volatile u16*)0x1F801128 != 0) {
            now += *(volatile u16*)0x1F801128;
        } else {
            now += 0x10000;
        }
    }
    if (!(*(volatile u16*)0x1F801124 & 0x200)) {
        elapsed = (now - D_8007B198) >> 3;
        limit = D_8007F6FC;
    } else {
        elapsed = now - D_8007B198;
        limit = D_8007F6FC;
    }
    return elapsed >= limit;
}
