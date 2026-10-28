// SPDX-License-Identifier: AGPL-3.0-or-later

#include "types.h"
#include "globals.h"

// Command handler (table D_8006E7EC): raises D_800778C8 to the command's
// value at +0x18.
void func_8002CD08(void* arg0) {
    // Reading the global first keeps the ROM's load order.
    s32 current = D_800778C8;
    s32 value = M2C_FIELD(arg0, s32*, 0x18);

    if (current < value) {
        D_800778C8 = value;
    }
}
