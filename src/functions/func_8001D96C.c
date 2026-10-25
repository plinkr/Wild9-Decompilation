// SPDX-License-Identifier: AGPL-3.0-or-later

#include "types.h"
#include "globals.h"

void func_8001D96C(s32 arg0, s32 arg1) {
    if (((D_8007B37C != 0) && (D_8007754C != 6)) || ((arg1 & 0xFF) == 0)) {
        // !FAKE: indexing D_80077708 directly folds the address differently
        *(s32*)((u8*)D_80077708 + (arg0 << 2)) = arg1 & 0xFF;
    }
}
