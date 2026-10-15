// SPDX-License-Identifier: AGPL-3.0-or-later
#include "functions.h"
#include "globals.h"

void func_8001A5D4(void* arg0, void* arg1) {
    M2C_FIELD(arg0, s32*, 0x2C) =
        (s32)(M2C_FIELD(arg1, s32*, 0x2EC) + M2C_FIELD(arg1, s32*, 0x1F8));
    M2C_FIELD(arg0, s32*, 0x30) =
        (s32)(M2C_FIELD(arg1, s32*, 0x2F0) + M2C_FIELD(arg1, s32*, 0x218));
    M2C_FIELD(arg0, s32*, 0x34) =
        (s32)(M2C_FIELD(arg1, s32*, 0x2F4) + M2C_FIELD(arg1, s32*, 0x238));
}
