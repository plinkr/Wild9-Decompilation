// SPDX-License-Identifier: AGPL-3.0-or-later
// https://decomp.me/scratch/DY5eg

#include "types.h"
#include "globals.h"
#include "decomp.h"
#include "functions.h"

void func_8003CEEC(void) {
    s32 var_v1;
    s32 var_idx;
    s16* pB5C;
    Ctx* ctx;
    Ctx* p44;
    s32 ret;
    u16 tmp;
    u16 sum2;
    s32 var_s0;
    register s32 var_s1 asm("s1");
    s32 var_s2;
    register s32 var_s3 asm("s3");

    var_s1 = 0;
    D_80077838 = 1;
    {
        s32* matrix = D_80077AC4;
        register s32 ai asm("a0") = 0;
        s32 vi = 0;
        register s32 i asm("v1") = 0;
        s32 cond = 0;
        do {
            i = 0;
            vi = var_s1 - 6;
            cond = (u32)vi < 4;
            ai = var_s1 * 0x10;
        loop_2:
            if (cond) {
                if (i >= 6) {
                    if (i < 0xA) {
                        *(s32*)(ai * 4 + (s32)matrix) = 1;
                        goto loop_3;
                    }
                    goto block_6;
                }
                vi = ai * 4;
                goto block_7;
            } else {
            block_6:
                vi = ai * 4;
            block_7:
                *(s32*)(vi + (s32)matrix) = 0;
            }
        loop_3:
            i += 1;
            ai += 1;
            if (i < 0x10) {
                goto loop_2;
            }
            var_s1 += 1;
        } while (var_s1 < 0x10);
    }

    var_s1 = 0;
    if (D_80077A44->count > 0) {
        var_s3 = -0x800;
        var_s2 = var_s1;
        var_s0 = var_s1;
        do {
            *(s16*)(var_s0 + (s32)D_80077848) = 0;
            ret = func_8001F7B4();
            *(s32*)(var_s2 + (s32)D_80077AFC) = ret & 0x7FFF;
            ret = func_8001F7B4();
            *(s32*)(var_s2 + (s32)D_80077AFC + 8) = ret & 0x7FFF;
            var_v1 = *(s32*)(var_s2 + (s32)D_80077AFC);
            var_idx = ((var_v1 >> 11) << 4) + ((ret & 0x7FFF) >> 11);
            if (D_80077AC4[var_idx] == D_80077838) {
                ret = func_8001F7B4();
                *(s16*)(var_s0 + (s32)D_80077920) = (ret & 3) + 1;
            } else {
                D_80077AC4[var_idx] = D_80077838;
                *(s16*)(var_s0 + (s32)D_80077920) = 0;
                ret = func_8001F7B4();
                pB5C = (s16*)(var_s0 + (s32)D_80077B5C);
                *(s16*)(var_s0 + (s32)D_80077AC0) = ret & 0xFFF;
                p44 = D_80077A44;
                *pB5C = 0;
                if (p44 == &D_8006FA94) {
                    *(s16*)(var_s0 + (s32)D_80077B60) = 0;
                }

                ret = func_8001F7B4();
                *(s16*)(var_s0 + (s32)D_80077A0C) = ret & 1;
                ret = func_8001F7B4();
                if ((ret & 0xFFF) >= 0xE75) {
                    if ((D_80077A44 == &D_8006F9A4) &&
                        ((func_8001F7B4() & 0xFFF) >= 0xE75)) {
                        sum2 = 4;
                        *(s16*)(var_s0 + (s32)D_80077A0C) = sum2;
                    } else {
                        tmp = *(u16*)(var_s0 + (s32)D_80077A0C);
                        ctx = D_80077A44;
                        sum2 = tmp + 2;
                        *(u16*)(var_s0 + (s32)D_80077A0C) = sum2;
                        if ((ctx->unk40 == 1) && ((s16)sum2 == 2)) {
                            *(s16*)(var_s0 + (s32)D_80077AC0) = 0;
                        }
                    }
                }
                ret = func_8001F7B4();
                *(s32*)(var_s2 + (s32)D_80077AFC + 4) = 0;
                *(s32*)(var_s2 + (s32)D_80077AFC) =
                    ((*(s32*)(var_s2 + (s32)D_80077AFC) - 0x4000) & var_s3) +
                    (ret & 0x3FF);
                ret = func_8001F7B4();
                *(s32*)(var_s2 + (s32)D_80077AFC + 8) =
                    ((*(s32*)(var_s2 + (s32)D_80077AFC + 8) - 0x4000) &
                     var_s3) +
                    (ret & 0x3FF);
            }
            var_s2 += 0x10;
            var_s0 += 2;
            var_s1 += 1;
        } while (var_s1 < D_80077A44->count);
    }
}
