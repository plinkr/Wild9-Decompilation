// SPDX-License-Identifier: AGPL-3.0-or-later
// https://decomp.me/scratch/Cx3h3

#include "types.h"
#include "functions.h"

// Interpolates the 0x18-byte output records between the previous key (the
// last record whose flag 0x1 at +0xF is clear) and the current one, using
// the time values at +0x1C of the 0x20-byte input records.
void func_800111FC(s32 arg0, void* arg1) {
    struct {
        volatile s32 d0;
        volatile s32 d1;
        volatile s32 d2;
        volatile s32 pad;
        s32 d3;
    } diffs;
    register u8* input asm("a2") = (u8*)arg1;
    register u8* output asm("s1") = (u8*)arg0;
    u8* var_s0;
    register u8* var_t7 asm("t7");
    register u8* var_t9 asm("t9");
    register u8* var_t8 asm("t8");
    register u8* var_t6 asm("t6");
    register s32 temp_t5 asm("t5");
    register s32 delta asm("v1");
    s32 temp_s2;
    s32 temp_fp;
    s32 temp_s7;
    s32 temp_s6;
    s32 temp_s5;
    register s32 temp_s4 asm("s4");
    u8* var_v1;
    register s32 tmpv asm("s3");
    register s32 q0 asm("a1");
    register s32 q1 asm("a2");
    register s32 q2 asm("a3");
    register s32 q3 asm("t0");
    register s32 q4 asm("t1");
    register s32 q5 asm("t2");
    register s32 q6 asm("t3");
    register s32 q7 asm("a0");
    register s32 q8 asm("t4");

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
    {
        register s32 t5a asm("v1");
        register s32 t5b asm("v0");
        t5a = *(s32*)(input + 0x1C);
        t5b = *(s32*)(var_s0 + 0x1C);
        temp_t5 = t5a - t5b;
    }
    {
        register s32 ra1 asm("a1");
        register s32 ra0 asm("a0");
        register s32 rv1 asm("v1");
        register s32 rv0 asm("v0");

        ra1 = *(s16*)(output + 0);
        ra0 = *(s16*)(output + 2);
        rv1 = *(s16*)(var_t7 + 0);
        rv0 = *(s16*)(var_t7 + 2);
        ra1 = ra1 - rv1;
        ra0 = ra0 - rv0;
        diffs.d0 = ra1;
        diffs.d1 = ra0;

        ra1 = *(s16*)(output + 4);
        rv1 = *(s16*)(var_t7 + 4);
        ra0 = *(s16*)(output + 6);
        rv0 = *(s16*)(var_t7 + 6);
        ra1 = ra1 - rv1;
        temp_fp = ra0 - rv0;
        diffs.d2 = ra1;

        ra1 = *(s16*)(output + 8);
        rv1 = *(s16*)(var_t7 + 8);
        ra0 = *(s16*)(output + 0xA);
        rv0 = *(s16*)(var_t7 + 0xA);
        temp_s7 = ra1 - rv1;
        temp_s6 = ra0 - rv0;

        ra1 = *(s16*)(output + 0xE);
        ra0 = *(s16*)(var_t7 + 0xE);
        rv1 = *(s16*)(var_t7 + 0x10);
        rv0 = *(s16*)(var_s0 + 8);
        temp_s5 = ra1 - ra0;
        // !FAKE: scheduling barrier. Without it GCC emits "rv1 - rv0" before
        // "temp_s5 = ra1 - ra0" and delays the load of var_t7 + 0xE.
        __asm__ volatile("");
        rv1 = rv1 - rv0;
        temp_s2 = rv1 & 0xFFF;

        rv0 = *(s16*)(output + 0x10);
        ra0 = *(s16*)(input + 8);
        rv1 = *(s16*)(var_t7 + 0x12);
        rv0 = rv0 - ra0;
        rv0 = rv0 & 0xFFF;
        rv0 = rv0 - temp_s2;
        rv0 = rv0 + 0x800;
        rv0 = rv0 & 0xFFF;
        temp_s4 = rv0 - 0x800;

        ra0 = *(s16*)(output + 0x12);
        ra0 = ra0 - rv1;
        diffs.d3 = ra0;
    }

    if (var_t9 >= output) {
        return;
    }

    var_t8 = var_s0 + 0x28;
    var_t6 = var_t7 + 0x2A;
    do {
        register s32 prod asm("v0");
        delta = *(s32*)(var_t8 + 0x14);
        delta = delta - *(s32*)(var_s0 + 0x1C);

        tmpv = diffs.d0;
        prod = tmpv * delta;
        q0 = prod / temp_t5;
        tmpv = diffs.d1;
        prod = tmpv * delta;
        q1 = prod / temp_t5;
        tmpv = diffs.d2;
        prod = tmpv * delta;
        q2 = prod / temp_t5;
        prod = temp_fp * delta;
        q3 = prod / temp_t5;
        prod = temp_s7 * delta;
        q4 = prod / temp_t5;
        prod = temp_s6 * delta;
        q5 = prod / temp_t5;
        prod = temp_s5 * delta;
        q6 = prod / temp_t5;
        prod = temp_s4 * delta;
        q7 = prod / temp_t5;
        tmpv = *(volatile s32*)&diffs.d3;
        delta = tmpv * delta;
        q8 = delta / temp_t5;

        *(s16*)var_t9 = (u16) * (u16*)var_t7 + q0;
        *(s16*)(var_t6 - 0x10) = (u16) * (u16*)(var_t7 + 2) + q1;
        *(s16*)(var_t6 - 0xE) = (u16) * (u16*)(var_t7 + 4) + q2;
        *(s16*)(var_t6 - 0xC) = (u16) * (u16*)(var_t7 + 6) + q3;
        *(s16*)(var_t6 - 0xA) = (u16) * (u16*)(var_t7 + 8) + q4;
        *(s16*)(var_t6 - 8) = (u16) * (u16*)(var_t7 + 0xA) + q5;

        var_t9 += 0x18;

        *(s16*)(var_t6 - 4) = (u16) * (u16*)(var_t7 + 0xE) + q6;
        *(s16*)(var_t6 - 0x2) = (*(u16*)var_t8 + (q7 + temp_s2)) & 0xFFF;

        var_t8 += 0x20;

        *(s16*)var_t6 = (u16) * (u16*)(var_t7 + 0x12) + q8;

        var_t6 += 0x18;
    } while (var_t9 < output);
}
