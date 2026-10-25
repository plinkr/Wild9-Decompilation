// SPDX-License-Identifier: AGPL-3.0-or-later

#include "functions.h"

void func_800665B0(void* arg0, s8 arg1) {
    M2C_FIELD(arg0, s8*, 0x37) = 0x47;
    M2C_FIELD(arg0, void**, 0x2C) = (void*)(arg0 + 0x24);
    M2C_FIELD(arg0, s8*, 0x24) = arg1;
    M2C_FIELD(arg0, s8*, 0x36) = 1;
}
