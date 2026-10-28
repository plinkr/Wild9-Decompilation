// SPDX-License-Identifier: AGPL-3.0-or-later

#include "types.h"
#include "functions.h"
#include "globals.h"

// Copies the table slot selected by a stream byte into +0x60.
s32 func_80034264(void* arg0) {
    s32 index = (s8)*D_8007782C;
    s32 value = M2C_FIELD((u8*)arg0 + (index << 2), s32*, 8);

    D_8007782C++;
    M2C_FIELD(arg0, s32*, 0x60) = value;
    return 1;
}
