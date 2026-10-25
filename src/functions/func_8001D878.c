// SPDX-License-Identifier: AGPL-3.0-or-later

#include "types.h"
#include "globals.h"

void func_8001D878(s32 arg0) {
    D_80077B84 = arg0;
    if (arg0 != 0) {
        D_8007754C = 2;
    } else {
        D_8007754C = 0;
    }
}
