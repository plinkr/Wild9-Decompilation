// SPDX-License-Identifier: AGPL-3.0-or-later

#include "types.h"
#include "functions.h"
#include "globals.h"
#include "include_asm.h"
#include "decomp.h"

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
