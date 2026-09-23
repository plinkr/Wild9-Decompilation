// SPDX-License-Identifier: AGPL-3.0-or-later
// https://decomp.me/scratch/axmWc

#include "types.h"

#define ADDR_MASK 0xFFFFFF

void func_800101D8(s32* base, s32 count) {
    s32 i;
    s32* current;
    s32* run_start;

    i = 0;
    current = base + count - 1;
    run_start = (s32*)i; // forces `move a2,a3`

    if (count > 0) {
        do {
            if (*current == (((s32)current - 4) & ADDR_MASK)) {
                if (run_start == (s32*)0) {
                    run_start = current;
                }
            } else if (run_start != (s32*)0) {
                *run_start = (s32)current & ADDR_MASK;
                run_start = (s32*)0;
            }

            i++;
            current--;
        } while (i < count);
    }

    if (run_start != (s32*)0) {
        *run_start = ADDR_MASK;
    }
}
