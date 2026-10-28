// SPDX-License-Identifier: AGPL-3.0-or-later

#include "types.h"
#include "functions.h"
#include "globals.h"

// Skips a NUL-terminated string in the D_8007782C stream.
s32 func_8003A610(void) {
    u8 c;

    do {
        c = *D_8007782C;
        D_8007782C++;
    } while (c != 0);
    return 1;
}
