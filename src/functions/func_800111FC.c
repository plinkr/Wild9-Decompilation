// SPDX-License-Identifier: AGPL-3.0-or-later
// https://decomp.me/scratch/Cx3h3
// WIP

#include "types.h"
#include "functions.h"

void func_800111FC(s32 arg0, void* arg1) {
    volatile s32 sp0;
    volatile s32 sp4;
    volatile s32 sp8;
    s32 unused;
    s32* punused = &unused;
    volatile s32 sp10;
    u8* input = (u8*)arg1;
    register u8* output asm("s1") = (u8*)arg0;
    u8* var_s0;
    register u8* var_t7 asm("t7");
    register u8* var_t9 asm("t9");
    register u8* var_t8 asm("t8");
    u8* var_t6;
    register s32 temp_t5 asm("t5");
    register s32 delta asm("v1");
    s32 temp_s2;
    register s32 temp_fp asm("fp");
    register s32 temp_s7 asm("s7");
    register s32 temp_s6 asm("s6");
    register s32 temp_s5 asm("s5");
    register s32 temp_s4 asm("s4");
    u8* var_v1;
    register s32 tmpv asm("s3");
    s32 q0;
    s32 q1;
    s32 q2;
    s32 q3;
    s32 q4;
    s32 q5;
    s32 q6;
    s32 q7;
    s32 q8;

    if (*(s32*)(input + 0x1C) == 0) {
        return;
    }

    var_s0 = input - 0x20;
    if (*(u8*)(input + 0xF) & 1) {
        return;
    }

    var_t7 = output - 0x18;
    if (*(s32*)(var_s0 + 0x1C) != 0) {
        var_v1 = input - 4;
        do {
            if (!(*(u8*)(var_v1 - 0xD) & 1)) {
                goto loop_done;
            }
            var_v1 -= 0x20;
            var_t7 -= 0x18;
            var_s0 -= 0x20;
        } while (*(s32*)var_v1 != 0);
    }
loop_done:
    var_t9 = var_t7 + 0x18;
    temp_t5 = *(s32*)(input + 0x1C) - *(s32*)(var_s0 + 0x1C);

    sp0 = *(s16*)(output + 0) - *(s16*)(var_t7 + 0);
    sp4 = *(s16*)(output + 2) - *(s16*)(var_t7 + 2);
    sp8 = *(s16*)(output + 4) - *(s16*)(var_t7 + 4);
    temp_fp = *(s16*)(output + 6) - *(s16*)(var_t7 + 6);
    temp_s7 = *(s16*)(output + 8) - *(s16*)(var_t7 + 8);
    temp_s6 = *(s16*)(output + 0xA) - *(s16*)(var_t7 + 0xA);
    temp_s5 = *(s16*)(output + 0xE) - *(s16*)(var_t7 + 0xE);

    temp_s2 = (*(s16*)(var_t7 + 0x10) - *(s16*)(var_s0 + 8)) & 0xFFF;
    temp_s4 = (*(s16*)(output + 0x10) - *(s16*)(input + 8)) & 0xFFF;
    temp_s4 = (temp_s4 - temp_s2 + 0x800) & 0xFFF;
    temp_s4 = temp_s4 - 0x800;
    sp10 = *(s16*)(output + 0x12) - *(s16*)(var_t7 + 0x12);

    if (var_t9 >= output) {
        return;
    }

    var_t8 = var_s0 + 0x28;
    var_t6 = var_t7 + 0x2A;
    do {
        delta = *(s32*)(var_t8 + 0x14) - *(s32*)(var_s0 + 0x1C);

        tmpv = sp0;
        q0 = tmpv * delta / temp_t5;
        tmpv = sp4;
        q1 = tmpv * delta / temp_t5;
        tmpv = sp8;
        q2 = tmpv * delta / temp_t5;
        q3 = temp_fp * delta / temp_t5;
        q4 = temp_s7 * delta / temp_t5;
        q5 = temp_s6 * delta / temp_t5;
        q6 = temp_s5 * delta / temp_t5;
        q7 = temp_s4 * delta / temp_t5;
        tmpv = sp10;
        q8 = tmpv * delta / temp_t5;

        *(s16*)var_t9 = (u16) * (u16*)var_t7 + q0;
        *(s16*)(var_t6 - 0x10) = (u16) * (u16*)(var_t7 + 2) + q1;
        *(s16*)(var_t6 - 0xE) = (u16) * (u16*)(var_t7 + 4) + q2;
        *(s16*)(var_t6 - 0xC) = (u16) * (u16*)(var_t7 + 6) + q3;
        *(s16*)(var_t6 - 0xA) = (u16) * (u16*)(var_t7 + 8) + q4;
        *(s16*)(var_t6 - 8) = (u16) * (u16*)(var_t7 + 0xA) + q5;

        var_t9 += 0x18;

        *(s16*)(var_t6 - 4) = (u16) * (u16*)(var_t7 + 0xE) + q6;
        *(s16*)(var_t6 - 2) = (*(u16*)var_t8 + (q7 + temp_s2)) & 0xFFF;

        var_t8 += 0x20;

        *(s16*)var_t6 = (u16) * (u16*)(var_t7 + 0x12) + q8;

        var_t6 += 0x18;
    } while (var_t9 < output);
}
