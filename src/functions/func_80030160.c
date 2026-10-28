// SPDX-License-Identifier: AGPL-3.0-or-later

#include "functions.h"
#include "globals.h"

void func_80030160(void* arg0) {
    if (M2C_FIELD(arg0, u16*, 0x12) == 1) {
        // Reading D_8007C948 as an array lets the `lui` of its address fill
        // the delay slot of the outer branch, as in the ROM.
        if ((M2C_FIELD(M2C_FIELD(arg0, void**, 0x48), s32*, 0x18) =
                 D_8007C948[0]) != 0) {
            M2C_FIELD(arg0, u8*, 0xA) = 0;
            M2C_FIELD(M2C_FIELD(arg0, void**, 0x48), u16*, 0x4) = 0x300;
            M2C_FIELD(M2C_FIELD(arg0, void**, 0x48), u16*, 0x0) = 0;
            M2C_FIELD(M2C_FIELD(arg0, void**, 0x48), u16*, 0x2) = 0x100;
            M2C_FIELD(arg0, s32*, 0x24) = -M2C_FIELD(arg0, s32*, 0x24) / 2;
            M2C_FIELD(arg0, s16*, 0x3C) = func_8001F7B4();
            M2C_FIELD(arg0, u16*, 0x12) = 100;
            M2C_FIELD(arg0, s32*, 0x4C) = 0;
        }
    }
}
