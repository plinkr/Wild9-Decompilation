// SPDX-License-Identifier: AGPL-3.0-or-later

#include "types.h"
#include "globals.h"

// Clears the flags word of the 100 entries of D_8007C2D8, last to first.
void func_800210F8(void) {
    s32 i;

    for (i = 99; i >= 0; i--) {
        D_8007C2D8[i].flags = 0;
    }
}
