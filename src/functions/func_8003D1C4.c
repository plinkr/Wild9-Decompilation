// SPDX-License-Identifier: AGPL-3.0-or-later
// https://decomp.me/scratch/9GbwW

#include "types.h"
#include "functions.h"
#include "globals.h"

void func_8003D1C4(void) {
    s32 sp10[3];
    s32 sp20[3];
    s32 var_s1;
    void** var_s0;
    void** temp_a1;
    void* temp_v0;
    void* temp_v0_2;
    s32 av;
    void* r;
    register void* rc asm("v1");

    av = *(s32*)((u8*)D_80077A44 + 0x24);
    D_80077838 = 1;
    r = func_8001E920(av * 0x10);
    av = *(s32*)((u8*)D_80077A44 + 0x24);
    D_80077AFC = r;
    r = func_8001E920(av * 0x10);
    av = *(s32*)((u8*)D_80077A44 + 0x24);
    D_8007792C = r;
    r = func_8001E920(av * 2);
    av = *(s32*)((u8*)D_80077A44 + 0x24);
    D_80077848 = r;
    r = func_8001E920(av * 2);
    av = *(s32*)((u8*)D_80077A44 + 0x24);
    D_80077AC0 = r;
    r = func_8001E920(av * 2);
    D_80077B5C = r;
    rc = D_80077A44;
    if (rc == (void*)&D_8006FA94[0]) {
        r = func_8001E920(*(s32*)((u8*)rc + 0x24) * 2);
        D_80077B60 = r;
    }

    var_s1 = 0;
    av = *(s32*)((u8*)D_80077A44 + 0x24);
    r = func_8001E920(av * 2);
    av = *(s32*)((u8*)D_80077A44 + 0x24);
    D_80077920 = r;
    r = func_8001E920(av * 2);
    av = *(s32*)((u8*)D_80077A44 + 0x24);
    D_80077A0C = r;
    r = func_8001E920(0x400);
    var_s0 = (void**)&D_8007C160[0];
    D_80077AC4 = r;

    sp10[0] = 0;
    sp10[1] = 0;
    sp10[2] = 0;
    sp20[0] = 0;
    sp20[1] = 0;
    sp20[2] = 0;

    do {
        temp_v0 = func_80028B98(0xE, 0);
        temp_a1 = *(void**)((u8*)temp_v0 + 0x10);
        *(s32*)((u8*)temp_a1 + 0x160) = -1;
        *(s32*)((u8*)temp_a1 + 0x164) = -1;
        *(s32*)((u8*)temp_a1 + 0x168) = 0;
        *(u16*)((u8*)temp_a1 + 0x4) |= 0x104;
        *(s32*)((u8*)temp_a1 + 0x190) &= ~0xC0;
        func_8003C104(temp_v0);

        if (*(s32*)((u8*)D_80077A44 + 0x40) == 1) {
            temp_v0_2 = func_80027B64(0x65, &sp20[0], &sp10[0], 1);
            *var_s0 = temp_v0_2;
            *(s16*)((u8*)temp_v0_2 + 0x38) = 0x400;
            *(s16*)((u8*)*var_s0 + 0x3A) = -(s16)D_80077808;
            *(s16*)((u8*)*(void**)((u8*)*var_s0 + 0x48) + 0x4) = 0x80;
        }

        var_s1 += 1;
        var_s0 += 1;
    } while (var_s1 < 0x23);
}
