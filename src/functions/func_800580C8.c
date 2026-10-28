// SPDX-License-Identifier: AGPL-3.0-or-later

#include "types.h"
#include "globals.h"

void func_800580C8(s32 index, s32 value) {
    if (value != D_800752F8[index]) {
        D_800752F8[index] = value;
    }
}
