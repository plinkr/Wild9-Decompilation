// SPDX-License-Identifier: AGPL-3.0-or-later
#include "functions.h"
#include "globals.h"

void func_80020A64(s32 arg0, void* arg1) {
    if (M2C_FIELD(arg1, s32*, 0x9C) == 0) {
        M2C_FIELD(arg1, s32*, 0x9C) = arg0;
    }
    M2C_FIELD(arg1, s32*, 0xA0) = (s32)(M2C_FIELD(arg1, s32*, 0xA0) + 1);
}
