// SPDX-License-Identifier: AGPL-3.0-or-later

#include "types.h"
#include "decomp.h"
#include "globals.h"

void func_8001DA34(s32 index, s32 arg1, s32 value) {
    D_8007C100_Entry* entry;

    if (index < 2) {
        entry = &((D_8007C100_Entry*)D_8007C100)[index];
        if (value >= entry->unk0) {
            entry->unk0 = value;
            entry->unk4 = arg1;
        }
    }
}
