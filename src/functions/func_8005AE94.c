// SPDX-License-Identifier: AGPL-3.0-or-later
#include "functions.h"

void func_8005AE94(void* arg0, s32 arg1, s32 arg2) {
    s32 var_v1;

    M2C_FIELD(arg0, s8*, 3) = 2;
    var_v1 = 0xE6000000;
    if (arg1 != 0) {
        var_v1 = 0xE6000002;
    }
    M2C_FIELD(arg0, s32*, 4) = (s32)(var_v1 | (arg2 != 0));
    M2C_FIELD(arg0, s32*, 8) = 0;
}
