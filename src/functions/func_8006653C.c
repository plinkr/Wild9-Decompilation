// SPDX-License-Identifier: AGPL-3.0-or-later
#include "functions.h"

void func_8006653C(void* arg0, s8 arg1) {
    M2C_FIELD(arg0, s8*, 0x37) = 0x43;
    M2C_FIELD(arg0, void**, 0x2C) = (void*)(arg0 + 0x24);
    M2C_FIELD(arg0, s8*, 0x24) = arg1;
    M2C_FIELD(arg0, s8*, 0x36) = 1;
}
