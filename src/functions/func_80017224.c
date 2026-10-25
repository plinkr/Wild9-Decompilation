// SPDX-License-Identifier: AGPL-3.0-or-later

#include "types.h"
#include "functions.h"
#include "decomp.h"

void func_80017224(void* arg0) {
    s32 angle;
    register s32 result asm("a0");

    if ((M2C_FIELD(arg0, s32*, 0x190) & 0x40000) &&
        (M2C_FIELD(arg0, u8*, 0x1D4) != 0x1B)) {
        angle = M2C_FIELD(arg0, s16*, 0x302);
        if (angle > 0x800) {
            angle -= 0x1000;
        }

        result = func_80024300(angle, 0xB000, 8);
        M2C_FIELD(arg0, s32*, 0x1E8) += result;
        M2C_FIELD(arg0, s32*, 0x20C) += result;
    }
}
