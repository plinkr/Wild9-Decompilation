// SPDX-License-Identifier: AGPL-3.0-or-later
#include "functions.h"

s32 func_80017C20(s32 arg0, s32 arg1, s32 arg2) {
    s32 var_a0;
    s32 var_v0;

    var_a0 = arg0;
    if (var_a0 < arg1) {
        var_a0 += arg2;
        var_v0 = arg1 < var_a0;
        goto block_4;
    }
    if (arg1 < var_a0) {
        var_a0 -= arg2;
        var_v0 = var_a0 < arg1;
    block_4:
        if (var_v0 != 0) {
            var_a0 = arg1;
        }
    }
    return var_a0;
}
