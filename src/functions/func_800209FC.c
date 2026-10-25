// SPDX-License-Identifier: AGPL-3.0-or-later

#include "types.h"
#include "globals.h"

// Returns the 32-byte entry `index` of D_8006A588; out-of-range indices fall
// back to entry 0.
u8* func_800209FC(u32 index) {
    if (index >= 0xF0) {
        index = 0;
    }
    return &D_8006A588[index * 32];
}
