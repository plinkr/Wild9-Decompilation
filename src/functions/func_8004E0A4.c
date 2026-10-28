// SPDX-License-Identifier: AGPL-3.0-or-later

#include "types.h"
#include "functions.h"
#include "globals.h"

// Copies the three parameter words into +0x2BC..+0x2C4 of `arg1`.
void func_8004E0A4(s32 arg0, void* arg1, s32* arg2) {
    M2C_FIELD(arg1, s32*, 0x2BC) = arg2[1];
    M2C_FIELD(arg1, s32*, 0x2C0) = arg2[2];
    M2C_FIELD(arg1, s32*, 0x2C4) = arg2[3];
}
