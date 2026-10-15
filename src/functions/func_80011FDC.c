// SPDX-License-Identifier: AGPL-3.0-or-later

#include "types.h"
#include "functions.h"
#include "globals.h"

void func_80011FDC(void) {
    s32* base = D_8007B350;
    register s32 flags asm("v1");
    register s32 value asm("v0");

    flags = base[0x308 / 4];
    value = flags & 1;
    if (value == 0) {
        value = flags | 1;
        base[0x308 / 4] = value;
        func_8001D3D4();
        func_8001D8DC(0, 0, 0);

        value = base[0x308 / 4] & 2;
        if (value == 0) {
            func_8004EE58();
        }
    }
}
