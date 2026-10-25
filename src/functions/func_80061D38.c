// SPDX-License-Identifier: AGPL-3.0-or-later

#include "functions.h"
#include "globals.h"

s32 func_80061D38(void* arg0) {
    *D_800762B4 = 2;
    *D_800762BC = M2C_FIELD(arg0, u8*, 0);
    *D_800762C0 = M2C_FIELD(arg0, u8*, 1);
    *D_800762B4 = 3;
    *D_800762B8 = M2C_FIELD(arg0, u8*, 2);
    *D_800762BC = M2C_FIELD(arg0, u8*, 3);
    *D_800762C0 = 0x20;
    return 0;
}
