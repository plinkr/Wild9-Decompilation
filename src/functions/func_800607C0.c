// SPDX-License-Identifier: AGPL-3.0-or-later
#include "functions.h"
#include "globals.h"

s32 func_800607C0(s32 arg0) {
    s32 temp_v0;

    temp_v0 = D_80075FF8;
    D_80075FF8 = arg0;
    return temp_v0;
}
