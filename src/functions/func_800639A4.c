// SPDX-License-Identifier: AGPL-3.0-or-later

#include "types.h"
#include "functions.h"
#include "globals.h"

/**
 * Returns -1 while D_8007B2E8 is set. Otherwise converts the value after the
 * one func_80060E08 reads from D_8007AAE0 into `loc` with func_80060D04 and
 * returns D_8007AAE4.
 */
s32 func_800639A4(u8* loc) {
    if (D_8007B2E8 != 0) {
        return -1;
    }
    func_80060D04(func_80060E08(D_8007AAE0) + 1, loc);
    return D_8007AAE4;
}
