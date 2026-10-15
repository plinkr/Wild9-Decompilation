// SPDX-License-Identifier: AGPL-3.0-or-later
#include "functions.h"
#include "globals.h"

void func_8005BDE8(s32 arg0) {
    *D_80075580 = 0x04000002;
    *D_80075584 = arg0;
    *D_80075588 = 0;
    *D_8007558C = 0x01000401;
}
