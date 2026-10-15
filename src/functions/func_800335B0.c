// SPDX-License-Identifier: AGPL-3.0-or-later
#include "functions.h"

s32 func_800335B0(void* arg0, s32 arg1, s32 arg2) {
    void* temp_v1;

    temp_v1 = M2C_FIELD(arg0, void**, 0x10);
    if ((M2C_FIELD(temp_v1, s16*, 0x2D8) == arg1) &&
        ((arg2 < 0) || (M2C_FIELD(temp_v1, s16*, 0x2DA) == arg2))) {
        return 1;
    }
    return 0;
}
