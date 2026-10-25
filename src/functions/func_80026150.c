// SPDX-License-Identifier: AGPL-3.0-or-later

#include "types.h"
#include "globals.h"

// Unregisters every object of the D_8007C8C0 table, last to first.
void func_80026150(void) {
    s32 i;

    for (i = 0x9F; i >= 0; i--) {
        D_8007C8C0[i].obj = NULL;
    }
}
