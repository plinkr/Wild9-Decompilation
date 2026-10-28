// SPDX-License-Identifier: AGPL-3.0-or-later

#include "types.h"
#include "functions.h"
#include "globals.h"

// Reads a little-endian unsigned 16-bit value from the D_8007782C stream.
u16 func_8003BEA8(void) {
    u8* cursor = D_8007782C;
    u16 value = cursor[0] | (cursor[1] << 8);

    D_8007782C = cursor + 2;
    return value;
}
