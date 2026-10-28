// SPDX-License-Identifier: AGPL-3.0-or-later

#include "types.h"
#include "globals.h"

// Reads a byte from the D_8007782C stream into the halfword at +0x58.
s32 func_800358AC(void* arg0) {
    u8 value = *D_8007782C;

    D_8007782C++;
    M2C_FIELD(arg0, u16*, 0x58) = value;
    return 0;
}
