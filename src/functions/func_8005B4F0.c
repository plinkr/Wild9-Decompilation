// SPDX-License-Identifier: AGPL-3.0-or-later

#include "types.h"

// Builds a GPU drawing offset command (0xE5).
u32 func_8005B4F0(u32 x, u32 y) {
    u32 hi = (y & 0x7FF) << 11;
    u32 lo = (x & 0x7FF) | 0xE5000000;

    return hi | lo;
}
