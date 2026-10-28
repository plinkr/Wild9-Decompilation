// SPDX-License-Identifier: AGPL-3.0-or-later

#include "types.h"
#include "functions.h"
#include "globals.h"

// Negates the table slot selected by a byte of the D_8007782C stream.
s32 func_80038B70(void* arg0) {
    u8 index = *D_8007782C;
    u8* cursor;
    s32 value;

    // !FAKE: storing the cursor back unchanged keeps `index` in a register,
    // so GCC emits the ROM's redundant `andi 0xFF` after the `lbu`.
    cursor = D_8007782C;
    D_8007782C = cursor;
    arg0 = (u8*)arg0 + (index << 2);
    value = M2C_FIELD(arg0, s32*, 8);
    D_8007782C++;
    M2C_FIELD(arg0, s32*, 8) = -value;
    return 1;
}
