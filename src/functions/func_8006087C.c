// SPDX-License-Identifier: AGPL-3.0-or-later
#include "functions.h"
#include "globals.h"

s32 func_8006087C(s32 arg0) {
    s32 temp_v0;

    temp_v0 = D_80075FEC;
    D_80075FEC = arg0;
    return temp_v0;
}
