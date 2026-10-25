// SPDX-License-Identifier: AGPL-3.0-or-later

#include "types.h"
#include "functions.h"

// Returns a pseudo-random value between arg0 and arg1, in either order.
s32 func_8001F820(s32 arg0, s32 arg1) {
    s32 base = arg0;
    s32 range;

    if (arg1 >= arg0) {
        range = arg1 - arg0;
    } else {
        range = arg0 - arg1;
        base = arg1;
    }

    if (range < 0) {
        range = -range;
    }

    return func_80024300(func_8001F7B4() & 0xFFFF, range, 0x10) + base;
}
