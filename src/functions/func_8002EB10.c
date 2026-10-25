// SPDX-License-Identifier: AGPL-3.0-or-later

#include "functions.h"

void func_8002EB10(void* arg0) {
    if ((u8)M2C_FIELD(arg0, u8*, 0xC) >= 0xE0U) {
        M2C_FIELD(arg0, s8*, 0xF) = -0x10;
        M2C_FIELD(arg0, s8*, 0x10) = -0x10;
        M2C_FIELD(arg0, s8*, 0x11) = -0x10;
        M2C_FIELD(arg0, s32*, 0x4C) = 0;
    }
}
