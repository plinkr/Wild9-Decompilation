// SPDX-License-Identifier: AGPL-3.0-or-later

#include "types.h"
#include "decomp.h"
#include "globals.h"

void func_8001DA00(void) {
    D_8007C100_Entry* table = (D_8007C100_Entry*)D_8007C100;
    s32 i;

    for (i = 0; i < 2; i++) {
        table[i].unk0 = 0;
        table[i].unk4 = 0;
        table[i].unk8 = 0;
        table[i].unkC = 0;
    }
}
