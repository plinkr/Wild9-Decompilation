// SPDX-License-Identifier: AGPL-3.0-or-later
// https://decomp.me/scratch/G8ipC

#include "types.h"
#include "functions.h"
#include "globals.h"

void func_80010E18(void) {
    s32 sp20;
    s32 sp24;
#define HANDLE (*(volatile s32*)&sp24)
    register s32 var_s0 asm("s0");
    register s32 var_s1 asm("s1");
    register u8* var_s2 asm("s2");
    register s32 var_s3 asm("s3");
    register u8* var_s4 asm("s4");
    register u8* var_s5 asm("s5");
    register u8* var_s6 asm("s6");
    register u8* var_s7 asm("s7");
    volatile u8* var_fp;
    s32 elementCount;
    s32 var_s0_2;
    s32 var_s0_3;
    s32 var_s1_3;
    s32 var_s1_5;

    if (D_80077B1C != 0) {
        HANDLE = func_8005F7A8(D_800683E8, 0);
        if (HANDLE != -1) {
            var_s2 = (u8*)&D_8007C7A8;
            func_80058FE4(var_s2, D_800683F8);

            var_s1 = 0;
            if (*var_s2 != 0) {
                register u8* scan asm("a0") = var_s2;
                do {
                    var_s1 += 1;
                } while (*(u8*)(var_s1 + (s32)scan) != 0);
            }

            var_s0 = 0;
            do {
                var_s0 +=
                    func_8005FA30(HANDLE, &D_8007C7A8[var_s0], var_s1 - var_s0);
            } while (var_s0 != var_s1);

            var_fp = (u8*)D_80077B1C;
            __asm__ volatile("" : "+r"(var_fp));
            sp20 = 0;
            if (D_8007786C > 0) {
                var_s7 = (u8*)(var_fp + 2);
                do {
                    var_s6 = (u8*)*(s32*)(var_s7 + 2);
                    var_s5 = (u8*)*(s32*)(var_s7 + 0xA);
                    elementCount = *(u16*)var_fp;
                    var_s3 = 0;
                    if (elementCount != 0) {
                        var_s2 = var_s5 + 0x10;
                        var_s4 = var_s6 + 0x1C;
                        do {
                            if ((var_s3 == 0) ||
                                (var_s3 == (elementCount - 1)) ||
                                ((func_80010B00((s32)(var_s5 - 0x18),
                                                var_s6 - 0x20) == 0) &&
                                 !(*(var_s4 - 0xD) & 1))) {
                                func_80058FE4(
                                    D_8007C7A8, D_80068420, *(u16*)var_s7,
                                    *(s32*)var_s4, (s32) * (s16*)(var_s2 - 0xE),
                                    (s32) * (s16*)(var_s2 - 0xC),
                                    (s32) * (s16*)(var_s2 - 2),
                                    (*(s16*)var_s2 - *(s16*)(var_s4 - 0x14)) &
                                        0xFFF);

                                var_s1_3 = 0;
                                if (D_8007C7A8[0] != 0) {
                                    while (D_8007C7A8[var_s1_3] != 0) {
                                        var_s1_3 += 1;
                                    }
                                }

                                var_s0_2 = 0;
                                do {
                                    var_s0_2 += func_8005FA30(
                                        HANDLE, &D_8007C7A8[var_s0_2],
                                        var_s1_3 - var_s0_2);
                                } while (var_s0_2 != var_s1_3);
                            }

                            var_s3 += 1;
                            var_s4 += 0x20;
                            var_s6 += 0x20;
                            var_s2 += 0x18;
                            var_s5 += 0x18;
                            elementCount = *(u16*)var_fp;
                        } while (var_s3 < elementCount);
                    }

                    func_80058FE4(D_8007C7A8, D_800774C8);
                    var_s1_5 = 0;
                    if (D_8007C7A8[0] != 0) {
                        while (D_8007C7A8[var_s1_5] != 0) {
                            var_s1_5 += 1;
                        }
                    }

                    var_s0_3 = 0;
                loop_28:
                    var_s0_3 += func_8005FA30(
                        HANDLE, &D_8007C7A8[var_s0_3], var_s1_5 - var_s0_3);
                    if (var_s0_3 != var_s1_5) {
                        goto loop_28;
                    }

                    var_s7 += 0x10;
                    var_fp += 0x10;
                    sp20 += 1;
                } while (sp20 < D_8007786C);
            }

            do {
            } while (func_8005F774(HANDLE) < 0);
        }
    }
}
