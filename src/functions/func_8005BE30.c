// SPDX-License-Identifier: AGPL-3.0-or-later
#include "functions.h"
#include "globals.h"

s32 func_8005BE30(s32 arg0) {
    *D_80075580 = arg0 | 0x10000000;
    return *D_8007557C & 0xFFFFFF;
}
