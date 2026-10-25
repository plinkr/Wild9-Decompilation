// SPDX-License-Identifier: AGPL-3.0-or-later

#include "functions.h"

s32 func_8005CCB4(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    return ((arg0 & 3) << 7) | ((arg1 & 3) << 5) | ((s32)(arg3 & 0x100) >> 4) |
           ((s32)(arg2 & 0x3FF) >> 6) | ((arg3 & 0x200) * 4);
}
