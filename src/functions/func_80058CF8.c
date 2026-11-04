// SPDX-License-Identifier: AGPL-3.0-or-later

// CFLAGS: -mno-split-addresses

#include "types.h"
#include "globals.h"

/**
 * tolower(). D_80075359 is the ctype table; bit 0x1 marks uppercase letters.
 */
s8 func_80058CF8(s8 c) {
    if (D_80075359[(u8)c] & 1) {
        c += 0x20;
    }
    return c;
}
