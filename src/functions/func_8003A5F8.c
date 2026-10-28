// SPDX-License-Identifier: AGPL-3.0-or-later

#include "types.h"
#include "functions.h"
#include "globals.h"

// Skips one byte of the D_8007782C stream.
s32 func_8003A5F8(void) {
    D_8007782C++;
    return 1;
}
