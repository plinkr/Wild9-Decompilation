// SPDX-License-Identifier: AGPL-3.0-or-later

#include "types.h"
#include "functions.h"
#include "globals.h"

// Reads an unsigned byte from the D_8007782C stream.
u8 func_8003BE8C(void) {
    u8 value = *D_8007782C;

    D_8007782C++;
    return value;
}
