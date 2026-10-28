// SPDX-License-Identifier: AGPL-3.0-or-later

#include "types.h"
#include "functions.h"
#include "globals.h"

// Jumps the D_8007782C stream to an unsigned 16-bit offset from the base at
// +0x4C.
s32 func_80034180(void* arg0) {
    s32 lo = D_8007782C[0];
    s32 hi = D_8007782C[1];

    D_8007782C += 2;
    D_8007782C = M2C_FIELD(arg0, u8**, 0x4C) + (lo | (hi << 8));
    return 1;
}
