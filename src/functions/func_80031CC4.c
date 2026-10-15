// SPDX-License-Identifier: AGPL-3.0-or-later
#include "functions.h"

void func_80031CC4(void* arg0) {
    s32 temp_a0;

    temp_a0 = M2C_FIELD(arg0, s32*, 0x18);
    if (temp_a0 < 0) {
        func_8001D490(temp_a0);
        return;
    }
    func_8001D4DC(temp_a0);
}
