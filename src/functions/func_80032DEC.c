// SPDX-License-Identifier: AGPL-3.0-or-later

#include "types.h"
#include "globals.h"

// Reads a byte index from the D_8007782C stream and copies the word it
// selects in the table at arg0 + 8.
s32 func_80032DEC(void* arg0) {
    u8 index = *D_8007782C;
    u8* cursor;
    void* target;
    s32 value;

    // !FAKE: storing the cursor back unchanged keeps `index` in a register,
    // so GCC emits the ROM's redundant `andi 0xFF` after the `lbu`.
    cursor = D_8007782C;
    D_8007782C = cursor;
    target = M2C_FIELD(M2C_FIELD(arg0, void**, 0x44), void**, 0x10);
    value = M2C_FIELD((u8*)arg0 + (index << 2), s32*, 8);
    D_8007782C++;
    M2C_FIELD(target, s32*, 0x2C) = value;
    return 1;
}
