// SPDX-License-Identifier: AGPL-3.0-or-later
#include "functions.h"

void func_8005CC78(s8* arg0, s8 arg1, s32 arg2) {
    s32 var_v0;
    s8* var_a0;

    var_a0 = arg0;
    var_v0 = arg2 - 1;
    if (arg2 != 0) {
        do {
            *var_a0 = arg1;
            var_v0 -= 1;
            var_a0 += 1;
        } while (var_v0 != -1);
    }
}
