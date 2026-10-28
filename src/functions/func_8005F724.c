// SPDX-License-Identifier: AGPL-3.0-or-later

#include "types.h"
#include "functions.h"
#include "globals.h"

// Copies the two halfwords at +0x1B0/+0x1B2 of D_80075E68.
void func_8005F724(u16* x, u16* y) {
    *x = M2C_FIELD(D_80075E68, u16*, 0x1B0);
    *y = M2C_FIELD(D_80075E68, u16*, 0x1B2);
}
