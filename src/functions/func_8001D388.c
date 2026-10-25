// SPDX-License-Identifier: AGPL-3.0-or-later

#include "functions.h"
#include "globals.h"

void func_8001D388(void) {
    if (!(D_80077538 & 0x20)) {
        if (D_80077538 & 0x10) {
            func_800608A4(0xC, 0, 0);
            D_80077538 &= ~0x10;
        }
    }
}
