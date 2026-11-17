// SPDX-License-Identifier: AGPL-3.0-or-later

// CFLAGS: -mno-split-addresses

#include "types.h"
#include "globals.h"

/**
 * Stores `value` in D_8007D3F8 and returns the previous contents.
 */
s32 func_80068340(s32 value) {
    s32 old = D_8007D3F8[0];

    D_8007D3F8[0] = value;
    return old;
}
