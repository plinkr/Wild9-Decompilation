// SPDX-License-Identifier: AGPL-3.0-or-later

#include "types.h"
#include "globals.h"

// D_8007C100 is a table of two 16-byte entries (also used by func_8001DA34,
// func_8001DA70 and func_8001DAAC).
typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
} D_8007C100_Entry;

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
