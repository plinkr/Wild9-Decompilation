// SPDX-License-Identifier: AGPL-3.0-or-later

#include "types.h"

/**
 * Copies `count` words from `src` to `dst`.
 */
void func_80064584(s32* dst, s32* src, u32 count) {
    u32 i;

    for (i = 0; i < count; i++) {
        *dst++ = *src++;
    }
}
