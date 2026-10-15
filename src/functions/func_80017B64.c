// SPDX-License-Identifier: AGPL-3.0-or-later
#include "functions.h"
#include "globals.h"

void func_80017B64(void* arg0) {
    void* temp_a0;

    temp_a0 = M2C_FIELD(arg0, void**, 0x10);
    if (M2C_FIELD(temp_a0, s32*, 0x190) & 0x80) {
        func_80017580(temp_a0);
        return;
    }
    func_800172A4(temp_a0);
}
