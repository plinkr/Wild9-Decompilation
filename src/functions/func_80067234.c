// SPDX-License-Identifier: AGPL-3.0-or-later

// CFLAGS: -fno-delayed-branch

#include "types.h"
#include "globals.h"

// Selects one of the two 0xF0-byte halves of D_8007ABC0 from bits 4-7 of
// arg0.
u8* func_80067234(s32 arg0) {
    u8* result = D_8007ABC0;

    if (arg0 & 0xF0) {
        result += 0xF0;
    }
    return result;
}
