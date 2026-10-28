// SPDX-License-Identifier: AGPL-3.0-or-later

#include "types.h"
#include "globals.h"

// Reads a little-endian signed 16-bit value from the D_8007782C stream and
// stores it shifted into 12-bit fixed point.
s32 func_80035B84(void* arg0) {
    s32 lo = D_8007782C[0];
    s32 hi = (s8)D_8007782C[1];
    void* target;

    D_8007782C += 2;
    target = M2C_FIELD(M2C_FIELD(arg0, void**, 0x44), void**, 0x10);
    M2C_FIELD(target, s32*, 0x1AC) = (lo | (hi << 8)) << 12;
    return 1;
}
