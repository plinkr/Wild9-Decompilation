// SPDX-License-Identifier: AGPL-3.0-or-later

#include "types.h"
#include "functions.h"
#include "decomp.h"

void func_800171E8(void* arg0) {
    register s32 delta asm("v0");
    register s32 angle asm("a1");

    angle = M2C_FIELD(arg0, s16*, 0x302);

    if (angle >= 0x801) {
        delta = angle - 0x1000;
    } else {
        delta = angle;
    }

    func_8001719C(arg0, delta << 8, 0x100000);
}
