// SPDX-License-Identifier: AGPL-3.0-or-later

#include "functions.h"

void func_8001719C(void* arg0, s32 arg1, s32 arg2) {
    s32 temp_v0;
    s32 var_a2;
    s32 var_v0;

    var_a2 = arg2;
    if (M2C_FIELD(arg0, s32*, 0x190) & 0x40000) {
        temp_v0 = M2C_FIELD(arg0, s32*, 0x1DC) + arg1;
        M2C_FIELD(arg0, s32*, 0x1DC) = temp_v0;
        if (arg1 < 0) {
            var_a2 = -var_a2;
            var_v0 = temp_v0 < var_a2;
        } else {
            var_v0 = var_a2 < temp_v0;
        }
        if (var_v0 != 0) {
            M2C_FIELD(arg0, s32*, 0x1DC) = var_a2;
        }
    }
}
