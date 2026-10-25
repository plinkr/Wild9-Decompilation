// SPDX-License-Identifier: AGPL-3.0-or-later

#include "functions.h"
#include "globals.h"

s32 func_80060890(s32 arg0) {
    s32 temp_v0;

    temp_v0 = D_80075FF0;
    D_80075FF0 = arg0;
    return temp_v0;
}
