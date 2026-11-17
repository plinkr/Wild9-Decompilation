// SPDX-License-Identifier: AGPL-3.0-or-later

#include "types.h"
#include "decomp.h"

/**
 * Returns ((+0xE3 + 1) / 2) * 4 + ((+0xE9 * 5 + 3) & 0xFFC) + 4 + +0xEC, all
 * read from `arg0`.
 */
s32 func_80065CF8(void* arg0) {
    s32 a = M2C_FIELD(arg0, u8*, 0xE3);
    s32 b = M2C_FIELD(arg0, u8*, 0xE9);
    s32 c = M2C_FIELD(arg0, u16*, 0xEC);
    s32 x = ((a + 1) / 2) * 4;
    s32 y = ((b * 5 + 3) & 0xFFC) + 4;

    return x + y + c;
}
