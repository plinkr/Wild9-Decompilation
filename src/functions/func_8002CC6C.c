// SPDX-License-Identifier: AGPL-3.0-or-later
#include "functions.h"

void func_8002CC6C(void* arg0) {
    void* temp_a0;

    temp_a0 = M2C_FIELD(arg0, void**, 0x44);
    func_800286C4(
        temp_a0, M2C_FIELD(M2C_FIELD(temp_a0, void**, 0x10), s32*, 0x3D8));
}
