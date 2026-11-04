// SPDX-License-Identifier: AGPL-3.0-or-later

// CFLAGS: -mno-split-addresses

#include "types.h"
#include "globals.h"

/**
 * toupper(). D_80075359 is the ctype table; bit 0x2 marks lowercase letters.
 */
s8 func_80058CC4(s8 c) {
    if (D_80075359[(u8)c] & 2) {
        c -= 0x20;
    }
    return c;
}
