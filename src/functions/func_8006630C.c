// SPDX-License-Identifier: AGPL-3.0-or-later
#include "functions.h"
#include "globals.h"

void func_8006630C(void* arg0) {
    M2C_FIELD(arg0, s8*, 0x37) = 0x4D;
    M2C_FIELD(arg0, s8*, 0x36) = 6;
    M2C_FIELD(arg0, s32*, 0x2C) = (s32)M2C_FIELD(arg0, s32*, 0x20);
}
