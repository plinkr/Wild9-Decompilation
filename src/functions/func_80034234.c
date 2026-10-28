// SPDX-License-Identifier: AGPL-3.0-or-later

#include "types.h"
#include "functions.h"
#include "globals.h"

// Moves the word at +0x60 into the table slot selected by a stream byte.
s32 func_80034234(void* arg0) {
    s32 index = (s8)*D_8007782C;
    s32 value;

    D_8007782C++;
    value = M2C_FIELD(arg0, s32*, 0x60);
    M2C_FIELD((u8*)arg0 + (index << 2), s32*, 8) = value;
    M2C_FIELD(arg0, s32*, 0x60) = 0;
    return 1;
}
