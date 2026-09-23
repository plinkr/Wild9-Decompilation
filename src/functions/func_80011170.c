// SPDX-License-Identifier: AGPL-3.0-or-later
// https://decomp.me/scratch/e3tzl

#include "types.h"
#include "functions.h"
#include "globals.h"
#include "include_asm.h"
#include "decomp.h"

void func_80011170(s32 arg0, void* arg1) {
    register void* s1 asm("s1");
    register s32 s2 asm("s2");
    register u8* s0 asm("s0");

    s1 = arg1;
    if (*(u16*)((u8*)s1 + 4) != 0) {
        s2 = arg0;
        s0 = (u8*)arg1 + 4;
        do {
            if (*(u8*)(s0 + 0x2B) & 1) {
                func_800110F8(s2, s1);
            } else if (func_80010B00(s2, s1) == 0) {
                return;
            }
            s2 += 0x18;
            s0 += 0x20;
            s1 = (u8*)s1 + 0x20;
        } while (*(u16*)s0 != 0);
    }
}
