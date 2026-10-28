// SPDX-License-Identifier: AGPL-3.0-or-later

#include "types.h"

// Clears `count` words at `dst`.
void func_800580F4(s32* dst, s32 count) {
    s32 i;

    for (i = count - 1; i != -1; i--) {
        *dst++ = 0;
    }
}
