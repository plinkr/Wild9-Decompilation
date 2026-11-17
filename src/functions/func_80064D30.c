// SPDX-License-Identifier: AGPL-3.0-or-later

// CFLAGS: -mno-split-addresses

#include "types.h"
#include "functions.h"
#include "globals.h"

/**
 * Initializes the 4-word block D_8007AB00: the callbacks func_80064DC4 and
 * func_80064D5C at words 1 and 2, words 0 and 3 cleared.
 */
void func_80064D30(void) {
    D_8007AB00[1] = (s32)func_80064DC4;
    D_8007AB00[2] = (s32)func_80064D5C;
    D_8007AB00[0] = 0;
    D_8007AB00[3] = 0;
}
