// SPDX-License-Identifier: AGPL-3.0-or-later
#include "functions.h"
#include "globals.h"

void func_800659F4(void* arg0, s8 arg1, s32 arg2, s8 arg3) {
    M2C_FIELD(arg0, s8*, 0x37) = arg1;
    M2C_FIELD(arg0, s32*, 0x2C) = arg2;
    M2C_FIELD(arg0, s8*, 0x36) = arg3;
}
