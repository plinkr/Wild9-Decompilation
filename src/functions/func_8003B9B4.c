// SPDX-License-Identifier: AGPL-3.0-or-later

#include "types.h"
#include "functions.h"
#include "globals.h"

// Clears the byte at +0x305 of the target if it equals the stream byte.
s32 func_8003B9B4(void* arg0) {
    void* target = M2C_FIELD(M2C_FIELD(arg0, void**, 0x44), void**, 0x10);
    u8 value = *D_8007782C;

    D_8007782C++;
    if (M2C_FIELD(target, u8*, 0x305) == value) {
        M2C_FIELD(target, u8*, 0x305) = 0;
    }
    return 1;
}
