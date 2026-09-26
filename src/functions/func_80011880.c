// SPDX-License-Identifier: AGPL-3.0-or-later
// https://decomp.me/scratch/DdsH8

#include "types.h"
#include "functions.h"
#include "globals.h"

void func_80011880(void) {
    s32 sp10;
    s32 sp14;
    s32 sp18;
    s32 sp1C;
    s32 sp20;
    s32 sp24;
    s32 temp_fp;
    s32 temp_s7;
    s16 temp_v1;
    s32 temp_s6;
    s32 var_s2;
    s32 var_s5;
    u8* temp_a1;
    u8* temp_s3;
    register u8* temp_s4 asm("s4");
    u8* temp_s1;
    register u8* var_s0 asm("s0");
    if (D_80077938 != 0) {
        temp_s4 = *(u8**)((u8*)D_80077938 + 0x10);
        temp_a1 = *(u8**)(temp_s4 + 0x2D0);
        if (temp_a1 != 0) {
            temp_v1 = *(s16*)(temp_s4 + 0x2DA);
            temp_s3 = *(u8**)(temp_a1 + 4) + (temp_v1 << 5);
            temp_s1 = *(u8**)(temp_a1 + 0xC) + (temp_v1 * 0x18);
            if (func_80010B00((s32)temp_s1, temp_s3) == 0) {
                var_s5 = 1;
                sp10 = *(s16*)(temp_s1 + 0);
                sp14 = *(s16*)(temp_s1 + 2);
                sp18 = *(s16*)(temp_s1 + 4);
                sp1C = *(s16*)(temp_s1 + 6);
                sp20 = *(s16*)(temp_s1 + 8);
                sp24 = *(s16*)(temp_s1 + 0xA);
                temp_fp = *(s16*)(temp_s1 + 0xE);
                temp_s6 = *(s16*)(temp_s1 + 0x10) - *(s16*)(temp_s3 + 8);
                temp_s7 = *(s16*)(temp_s1 + 0x12);
                temp_s3 += 0x20;
                temp_s1 += 0x18;
                var_s2 = *(s16*)(temp_s4 + 0x2DA) + 1;
                if (var_s2 < (s32) * (u16*)*(u8**)(temp_s4 + 0x2D0)) {
                    var_s0 = temp_s1 + 0x12;
                    do {
                        if (func_80010B00((s32)temp_s1, temp_s3) == 0) {
                            var_s5 = 0;
                        }

                        *(u16*)temp_s1 = (u16)sp10;
                        *(u16*)(var_s0 - 0x10) = (u16)sp14;
                        *(u16*)(var_s0 - 0xE) = (u16)sp18;
                        *(u16*)(var_s0 - 0xC) = (u16)sp1C;
                        *(u16*)(var_s0 - 0xA) = (u16)sp20;
                        *(u16*)(var_s0 - 8) = (u16)sp24;
                        *(s16*)(var_s0 - 4) = temp_fp;
                        *(s16*)(var_s0 - 2) =
                            (s16)((*(u16*)(temp_s3 + 8) + temp_s6) & 0xFFF);
                        *(s16*)var_s0 = temp_s7;
                        if (var_s5 == 0) {
                            break;
                        }
                        var_s2 += 1;
                        temp_s3 += 0x20;
                        var_s0 += 0x18;
                        temp_s1 += 0x18;
                    } while (var_s2 < (s32) * (u16*)*(u8**)(temp_s4 + 0x2D0));
                }
            }
        }
    }
}
