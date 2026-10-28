// SPDX-License-Identifier: AGPL-3.0-or-later

#include "types.h"
#include "globals.h"

// Reads a signed byte from the D_8007782C stream into the byte at +0x1C of
// the target.
s32 func_8003510C(void* arg0) {
    void* target = M2C_FIELD(M2C_FIELD(arg0, void**, 0x44), void**, 0x10);
    s32 value = (s8)*D_8007782C++;

    M2C_FIELD(target, u8*, 0x1C) = value;
    return 1;
}
