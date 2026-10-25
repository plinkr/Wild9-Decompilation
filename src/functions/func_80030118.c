// SPDX-License-Identifier: AGPL-3.0-or-later

#include "functions.h"

void func_80030118(void* arg0) {
    if ((M2C_FIELD(arg0, u16*, 0x12) == 1) &&
        (M2C_FIELD(arg0, s32*, 0xC) & 0xFFFFFF)) {
        M2C_FIELD(arg0, u16*, 0x12) = 0x3E8U;
        M2C_FIELD(arg0, s32*, 0x24) =
            (s32)((s32)-M2C_FIELD(arg0, s32*, 0x24) / 2);
    }
}
