// SPDX-License-Identifier: AGPL-3.0-or-later

#include "types.h"

// Clears `count` words at `dst`.
void func_8005839C(s32* dst, s32 count) {
    s32 i;

    for (i = count - 1; i != -1; i--) {
        *dst++ = 0;
    }
}
