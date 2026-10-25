// SPDX-License-Identifier: AGPL-3.0-or-later

#include "globals.h"

// Seeds the three-word state that func_8001F7B4 updates (pseudo-random
// generator: shift/xor/multiply step).
void func_8001F78C(void) {
    D_80077564 = 0x22AC8EE1;
    D_80077568 = 0x047AE927;
    D_8007756C = 0xD;
}
