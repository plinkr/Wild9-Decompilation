// SPDX-License-Identifier: AGPL-3.0-or-later
// https://decomp.me/scratch/9zTq0

#include "types.h"
#include "functions.h"
#include "func_types.h"
#include "globals.h"

void func_80011E18(void) {
    struct {
        u16 x;
        u16 y;
        s16 width;
        s16 height;
        s16 zero0;
        s16 zero1;
        s16 x2;
        s16 y2;
        s8 zero2;
        s8 zero3;
        s8 zero4;
        s8 zero5;
    } state;
    u8* input;
    s32* p;
    s32 flags;

    state.width = 0x140;
    state.x = 0;
    state.y = 0;
    state.height = 0xF0;
    state.zero0 = 0;
    state.zero1 = 0;
    p = D_8007C788;
    state.x2 = 0x100;
    state.y2 = 0xF0;
    state.zero2 = 0;
    state.zero3 = 0;
    state.zero4 = 0;
    state.zero5 = 0;

    if (p[1] & 0x80) {
        do {
            input = (u8*)D_8007C788;
            ((F576C4)func_800576C4)(0);
            func_8001DF7C(0);

            flags = *(s32*)(input + 4);
            if (flags & 4) {
                state.x -= 8;
            }
            if (flags & 8) {
                state.x += 8;
            }
            if (flags & 1) {
                state.y -= 8;
            }
            if (flags & 2) {
                state.y += 8;
            }

            func_8005A840(&state.x);
        } while (*(s32*)(input + 4) & 0x80);
    }
}
