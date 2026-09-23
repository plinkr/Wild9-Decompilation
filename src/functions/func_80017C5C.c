// SPDX-License-Identifier: AGPL-3.0-or-later
// https://decomp.me/scratch/1Id91

#include "types.h"
#include "functions.h"

s32 func_80017C5C(s32 arg0, s32 arg1) {
    s32 var_a0;
    s32 var_a1;

    var_a0 = arg0;
    var_a1 = arg1;
    if ((var_a1 < var_a0) || (var_a1 = -var_a1, (var_a0 < var_a1) != 0)) {
        var_a0 = var_a1;
    }
    return var_a0;
}
