// SPDX-License-Identifier: AGPL-3.0-or-later

#include "types.h"
#include "functions.h"
#include "globals.h"

void func_8001D490(void) {
    u8 buf;

    D_80077538 &= ~0x30;
    func_8001D344();
    D_8007752C = -1;
    buf = 0;
    func_800608A4(9, (s32)&buf, 0);
}
