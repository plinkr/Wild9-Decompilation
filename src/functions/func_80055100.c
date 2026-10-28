// SPDX-License-Identifier: AGPL-3.0-or-later

#include "types.h"
#include "globals.h"

// Clears the 250 words of D_8007B418 and of D_8007D430.
void func_80055100(void) {
    s32* p = D_8007B418;
    s32* q = D_8007D430;
    s32 i;

    for (i = 0; i < 250; i++) {
        *p++ = 0;
        *q++ = 0;
    }
}
