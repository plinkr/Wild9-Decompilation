// SPDX-License-Identifier: AGPL-3.0-or-later

#include "types.h"
#include "functions.h"
#include "globals.h"

void func_8005A010(s32 arg0) {
    if (D_8007547A >= 2) {
        D_80075474(D_800695E0, arg0);
    }
    M2C_FIELD(D_80075470, void (**)(s32), 0x3C)(arg0);
}
