// SPDX-License-Identifier: AGPL-3.0-or-later
// https://decomp.me/scratch/hvLh1

#include "types.h"
#include "globals.h"

void func_80011A50(void) {
    register void* root asm("v0");
    register u8* parent asm("a3");
    register u8* node asm("v1");
    register u8* output asm("a0");
    register u8* input asm("a2");
    register s32 index asm("a1");
    register s32 value asm("v0");

    root = D_80077938;
    if (root != 0) {
        parent = *(u8**)((u8*)root + 0x10);
        node = *(u8**)(parent + 0x2D0);
        if (node != 0) {
            input = *(u8**)(node + 4);
            value = *(u16*)node;
            output = *(u8**)(node + 0xC);

            if (value != 0) {
                register s32 value1900 asm("t2");
                register s32 value640 asm("t1");
                register s32 valueE9 asm("t0");

                index = 0;
                __asm__ volatile("" : "+r"(index));
                value1900 = -0x1900;
                value640 = -0x640;
                valueE9 = -0xE9;
                node = output + 0x12;
                do {
                    index += 1;
                    *(s16*)output = 0;
                    *(s16*)(node - 0x10) = 0;
                    *(s16*)(node - 0xE) = value1900;
                    *(s16*)(node - 0xC) = 0;
                    *(s16*)(node - 0xA) = value640;
                    *(s16*)(node - 8) = 0;
                    *(s16*)(node - 4) = valueE9;

                    value = *(u16*)(input + 8);
                    input += 0x20;
                    *(s16*)node = 0;
                    value = (value + 0x400) & 0xFFF;
                    *(s16*)(node - 2) = value;

                    value = *(u16*)*(u8**)(parent + 0x2D0);
                    output += 0x18;
                    node += 0x18;
                } while (index < value);
            }

            D_8006C394[0] = 0;
            D_8006C394[1] = 0;
            D_8006C394[2] = 0;
            D_8006C3A0[0] = 0;
            D_8006C3A0[1] = 0;
            D_8006C3A0[2] = 0;
        }
    }
}
