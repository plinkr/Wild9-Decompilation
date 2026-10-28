// SPDX-License-Identifier: AGPL-3.0-or-later

#include "types.h"
#include "functions.h"
#include "globals.h"

// Reads a little-endian signed 16-bit value from the D_8007782C stream and
// passes it to func_80033908 for the block at +0x190 of the target.
s32 func_8003395C(void* arg0) {
    s32 lo = D_8007782C[0];
    s32 hi = (s8)D_8007782C[1];
    void* target = M2C_FIELD(M2C_FIELD(arg0, void**, 0x44), void**, 0x10);

    D_8007782C += 2;
    func_80033908((u8*)target + 0x190, lo | (hi << 8));
    return 1;
}
