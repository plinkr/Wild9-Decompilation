// SPDX-License-Identifier: AGPL-3.0-or-later

#include "types.h"
#include "globals.h"

// Reads a little-endian 16-bit value from the D_8007782C stream into the
// halfword at +0x1C4 of the target.
s32 func_80034434(void* arg0) {
    s32 lo = D_8007782C[0];
    s32 hi = (s8)D_8007782C[1];
    void* target;

    D_8007782C += 2;
    target = M2C_FIELD(M2C_FIELD(arg0, void**, 0x44), void**, 0x10);
    M2C_FIELD(target, s16*, 0x1C4) = lo | (hi << 8);
    return 1;
}
