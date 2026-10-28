// SPDX-License-Identifier: AGPL-3.0-or-later

#include "types.h"
#include "functions.h"
#include "globals.h"

// Reads a little-endian signed 16-bit value from the D_8007782C stream.
s32 func_8003BF24(void) {
    s32 lo = D_8007782C[0];
    s32 hi = (s8)D_8007782C[1];

    D_8007782C += 2;
    return lo | (hi << 8);
}
