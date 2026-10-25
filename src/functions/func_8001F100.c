// SPDX-License-Identifier: AGPL-3.0-or-later

#include "types.h"
#include "globals.h"

void func_8001F100(void) {
    D_8007B1B8[0] = 1;
    D_8007B1B8[1] = 0x2B;
    *(u16*)(D_8007B1B8 + 6) = 1;
    *(u16*)(D_8007B1B8 + 4) = 0x10;
}
