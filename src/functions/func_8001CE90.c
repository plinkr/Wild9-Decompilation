// SPDX-License-Identifier: AGPL-3.0-or-later

#include "types.h"
#include "globals.h"

s32 func_8001CE90(void) {
    s32 value = (D_80077BB4 << 8) / D_800777DC;

    if (value > 0x100) {
        value = 0x100;
    }

    return value;
}
