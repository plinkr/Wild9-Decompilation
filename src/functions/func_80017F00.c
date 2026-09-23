// SPDX-License-Identifier: AGPL-3.0-or-later
// https://decomp.me/scratch/VzcuK

#include "types.h"
#include "functions.h"
#include "globals.h"
#include "include_asm.h"
#include "decomp.h"

void func_80017F00(u32 arg0, s32 arg1, s32 arg2) {
    s32 sp10[16];
    s32 sp50;

    register s32 var_s3 asm("s3") = arg1;
    register s32 (*var_s2)(u32, s32, s32, s32*) asm("s2");
    s32 (*temp_s2)(u32, s32, s32, s32*);

    s32 temp_a1;
    s32 temp_v0;
    s32 temp_v0_2;
    register s32 temp_v0_3 asm("v0");
    s32 temp_v0_4;
    s32 var_s0;
    s32 var_s0_2;
    s32 temp_v1;

    if (arg0 != 0) {
        if ((arg0 <= 0x1F7FFFFFU) ||
            ((u32)(arg0 + 0xE07FFC00) <= 0x607FFBFFU) || (arg0 > 0x80200000U)) {
            D_80077558 += 1;
            return;
        }
        var_s0 = arg1 >> 0xC;
        if (M2C_FIELD(arg0, s32*, 4) != 0) {
            arg1 = var_s0;
            if (M2C_FIELD(arg0, s32*, 0x24) == M2C_FIELD(arg0, s32*, 0x18)) {
                temp_s2 = func_80017D50;
            } else {
                temp_s2 = func_80017EE0;
            }
            var_s2 = temp_s2;
        loop_9:
            do {
                temp_v0 = var_s2(arg0, M2C_FIELD(arg0, s32*, 4), var_s0, &sp50);
                var_s0 -= temp_v0;
                if (temp_v0 != 0) {
                    goto loop_9;
                }
            } while (sp50 != 0);
            if (arg2 != 0) {
                *(W9Copy64*)sp10 = *(W9Copy64*)arg0;
                var_s0_2 = arg2 >> 1;
                if ((arg2 << 0xC) >= M2C_FIELD(arg0, s32*, 0x30)) {
                    var_s0_2 = -var_s0_2;
                }
            loop_17:
                do {
                    temp_v0_2 = var_s2((u32)sp10, sp10[1], var_s0_2, &sp50);
                    var_s0_2 -= temp_v0_2;
                    if (temp_v0_2 != 0) {
                        goto loop_17;
                    }
                } while (sp50 != 0);
                temp_v1 = M2C_FIELD(arg0, s32*, 0x30);
                temp_v0_3 = (arg2 << 0xC) < temp_v1;
                if (temp_v0_3 == 0) {
                    var_s0_2 = -var_s0_2;
                }
                if (var_s0_2 > 0) {
                    if (arg1 < 0) {
                        arg1 = -arg1;
                    }
                    if (temp_v0_3 == 0) {
                        temp_a1 = arg1 + 0x1E;
                        if (temp_a1 < var_s0_2) {
                            var_s0_2 = temp_a1;
                        }
                    } else if ((arg1 + 0x1E) < var_s0_2) {
                        var_s0_2 = -arg1 - 0x1E;
                    } else {
                        var_s0_2 = -var_s0_2;
                    }
                    M2C_FIELD(arg0, u16*, 8) =
                        (u16)(M2C_FIELD(arg0, u16*, 8) | ((u16*)sp10)[4]);
                loop_32:
                    do {
                        temp_v0_4 = var_s2(
                            arg0, M2C_FIELD(arg0, s32*, 4), var_s0_2, &sp50);
                        var_s0_2 -= temp_v0_4;
                        if (temp_v0_4 != 0) {
                            goto loop_32;
                        }
                    } while (sp50 != 0);
                }
            }
            func_800185C4(arg0);
        }
    }
}
