// SPDX-License-Identifier: AGPL-3.0-or-later

#include "functions.h"
#include "globals.h"

u32 func_8005AD6C(void) {
    return M2C_FIELD(D_80075470, u32(**)(), 0x38)() >> 0x1F;
}
