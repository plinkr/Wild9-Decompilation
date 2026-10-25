// SPDX-License-Identifier: AGPL-3.0-or-later

#include "functions.h"
#include "globals.h"

void func_8005F644(s16 arg0, s16 arg1) {
    M2C_FIELD(D_80075E68, s16*, 0x1B0) = arg0;
    M2C_FIELD(D_80075E68, s16*, 0x1B2) = arg1;
}
