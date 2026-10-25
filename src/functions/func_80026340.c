// SPDX-License-Identifier: AGPL-3.0-or-later

#include "types.h"
#include "globals.h"

// Advances the counter of every registered object; a counter wraps to zero
// when it reaches the limit stored at offset 4 of its object.
void func_80026340(void) {
    s32 i;

    for (i = 0; i < 0xA0; i++) {
        D_8007C8C0_Entry* entry = &D_8007C8C0[i];

        if (entry->obj != NULL) {
            s32 count = entry->count + 1;

            entry->count = count;
            if (count >= ((s32*)entry->obj)[1]) {
                entry->count = 0;
            }
        }
    }
}
