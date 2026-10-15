// SPDX-License-Identifier: AGPL-3.0-or-later
#include "functions.h"
#include "globals.h"

void func_8005F624(s32 arg0, s32 arg1) {
    M2C_FIELD(D_80075E68, s16*, 0x180) = (s16)(arg0 & 0x7FFF);
    M2C_FIELD(D_80075E68, s16*, 0x182) = (s16)(arg1 & 0x7FFF);
}
