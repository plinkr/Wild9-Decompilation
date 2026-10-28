// SPDX-License-Identifier: AGPL-3.0-or-later

#include "types.h"
#include "globals.h"

// Stores `value` in *D_800752E0 and returns the previous value.
s32 func_80057A70(u16 value) {
    s32 old = *D_800752E0;

    *D_800752E0 = value;
    return old;
}
