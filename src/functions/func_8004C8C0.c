// SPDX-License-Identifier: AGPL-3.0-or-later

#include "functions.h"

void func_8004C8C0(void* arg0) {
    void* temp_v0;

    temp_v0 = M2C_FIELD(arg0, void**, 0x10);
    func_8004C8F0(
        M2C_FIELD(temp_v0, s32*, 0x3E4), M2C_FIELD(temp_v0, s32*, 0x12C));
}
