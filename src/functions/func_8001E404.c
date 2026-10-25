// SPDX-License-Identifier: AGPL-3.0-or-later

#include "functions.h"

s32 func_8001E404(s32 arg0) {
    s32 var_v1;
    void* temp_s0;

    temp_s0 = (void*)(arg0 - 0x14);
    var_v1 = func_8001E340(temp_s0, 1);
    if ((var_v1 == 0) && (M2C_FIELD(temp_s0, s32*, 0x10) < 0)) {
        var_v1 = -6;
    }
    return var_v1;
}
