// SPDX-License-Identifier: AGPL-3.0-or-later
#include "functions.h"

void func_8003C174(void* arg0, s32 arg1, s32 arg2) {
    s32 var_a1;
    s32 var_a2;
    void* var_v1;

    var_a1 = arg1;
    var_a2 = arg2;
    var_v1 = M2C_FIELD(arg0, void**, 8);
    if ((var_a1 >= 0) || (var_a2 >= 0)) {
    loop_2:
        var_a2 -= 1;
        if (var_v1 != NULL) {
            if (var_a2 == -1) {
                M2C_FIELD(var_v1, u16*, 0xC) =
                    (u16)(M2C_FIELD(var_v1, u16*, 0xC) | 0x1002);
            }
            var_a1 -= 1;
            if (var_a1 == -1) {
                M2C_FIELD(var_v1, u16*, 0xC) =
                    (u16)(M2C_FIELD(var_v1, u16*, 0xC) & 0xEFFD);
            }
            var_v1 = M2C_FIELD(var_v1, void**, 4);
            if ((var_a1 >= 0) || (var_a2 >= 0)) {
                goto loop_2;
            }
        }
    }
}
