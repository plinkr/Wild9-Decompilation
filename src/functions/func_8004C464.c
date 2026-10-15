// SPDX-License-Identifier: AGPL-3.0-or-later
#include "functions.h"

void* func_8004C464(void* arg0) {
    void* temp_v0;

    temp_v0 = func_8001E920(0x101C);
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v0, s8*, 1) = -1;
        M2C_FIELD(temp_v0, s8*, 0) = 0;
        M2C_FIELD(temp_v0, s16*, 2) = 0x1E;
        M2C_FIELD(temp_v0, s32*, 4) =
            (s32)((s32)M2C_FIELD(arg0, s32*, 0) >> 0xC);
        M2C_FIELD(temp_v0, s32*, 8) =
            (s32)((s32)M2C_FIELD(arg0, s32*, 4) >> 0xC);
        M2C_FIELD(temp_v0, s32*, 0xC) =
            (s32)((s32)M2C_FIELD(arg0, s32*, 8) >> 0xC);
    }
    return temp_v0;
}
