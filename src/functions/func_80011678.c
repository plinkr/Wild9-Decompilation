// SPDX-License-Identifier: AGPL-3.0-or-later
// https://decomp.me/scratch/xH8Mh

#include "types.h"
#include "functions.h"
#include "globals.h"

void func_80011678(void) {
    s32 index;
    u8* input;
    u8* output;
    u8* object;
    s32 continueFlag;
    s32 current;
    u8* root;
    u8* node;
    u8* nodeA;
    u8* nodeB;
    u8* nodeT;
    u8* delta;
    u8* outputBase;
    u8* inputBase;
    s32 outputIndex;

    root = (u8*)D_80077938;
    if (root != 0) {
        object = *(u8**)(root + 0x10);
        nodeA = *(u8**)(object + 0x2D0);
        if (nodeA != 0) {
            index = *(s16*)(object + 0x2DA);
            input = *(u8**)(nodeA + 4) + (index << 5);
            output = *(u8**)(nodeA + 0xC) + index * 0x18;

            if (*(u8*)(input + 0xF) & 1) {
            loop_back:
                if (index != 0) {
                    index -= 1;
                    input -= 0x20;
                    output -= 0x18;
                    if (*(u8*)(input + 0xF) & 1) {
                        goto loop_back;
                    }
                }
            }

            func_80011170((s32)output, input);

            nodeB = *(u8**)(object + 0x2D0);
            continueFlag = 1;
            current = index;
            if (current < *(u16*)nodeB) {
                delta = (u8*)D_8006C394;
                do {
                    if (func_80010B00((s32)output, input) == 0) {
                        continueFlag = 0;
                    }

                    *(u16*)(output + 2) += *(u16*)(delta + 4);
                    *(u16*)(output + 4) += *(u16*)(delta + 8);
                    *(u16*)(output + 0xE) += *(u16*)&D_8006C3A0[0];
                    *(u16*)(output + 0x10) += *(u16*)&D_8006C3A0[1];

                    if (continueFlag == 0) {
                        break;
                    }

                    current += 1;
                    input += 0x20;
                    node = *(u8**)(object + 0x2D0);
                    output += 0x18;
                } while (current < *(u16*)node);
            }

            if (*(u16*)(input + 4) != 0) {
                func_800111FC((s32)(output + 0x18), input + 0x20);
            }

            nodeT = *(u8**)(object + 0x2D0);
            outputBase = *(u8**)(nodeT + 0xC);
            inputBase = *(u8**)(nodeT + 4);
            outputIndex = index << 1;
            outputIndex += index;
            outputIndex <<= 3;
            func_800111FC(
                (s32)(outputBase + outputIndex), inputBase + (index << 5));

            D_8006C394[0] = 0;
            D_8006C394[1] = 0;
            D_8006C394[2] = 0;
            D_8006C3A0[0] = 0;
            D_8006C3A0[1] = 0;
            D_8006C3A0[2] = 0;
        }
    }
}
