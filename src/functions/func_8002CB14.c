// SPDX-License-Identifier: AGPL-3.0-or-later
#include "functions.h"
#include "globals.h"

void func_8002CB14(void* arg0) {
    void* temp_a1;

    temp_a1 = M2C_FIELD(arg0, void**, 0x44);
    func_800286C4(
        M2C_FIELD(M2C_FIELD(temp_a1, void**, 0x10), s32*, 0x3D8), temp_a1);
}
