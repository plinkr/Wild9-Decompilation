// SPDX-License-Identifier: AGPL-3.0-or-later

#include "types.h"
#include "globals.h"

// Keeps the first value received and counts every call.
void func_80020A38(s32 arg0) {
    if (D_800778C4 == 0) {
        D_800778C4 = arg0;
    }
    D_80077810++;
}
