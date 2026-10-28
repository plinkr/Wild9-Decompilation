// SPDX-License-Identifier: AGPL-3.0-or-later

#include "types.h"
#include "globals.h"

// Clears the 50 words of D_8007B350.
void func_800550DC(void) {
    s32* p = D_8007B350;
    s32 i;

    for (i = 49; i >= 0; i--) {
        *p++ = 0;
    }
}
