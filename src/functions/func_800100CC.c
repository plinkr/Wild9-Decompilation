// SPDX-License-Identifier: AGPL-3.0-or-later
// https://decomp.me/scratch/xxGXE

#include "types.h"
#include "functions.h"
#include "globals.h"

void func_800100CC(void) {
    register s32 current asm("v0");
    register s32 temp_v1 asm("v1");

    func_8001D5FC();

    current = D_800774C4;
    if (current != 0) {
        temp_v1 = current + 1;
        D_800774C4 = temp_v1;

        if (temp_v1 != 0x11) {
            goto secondCheck;
        }

        func_8005A840(D_8007D31C);
        __asm__ volatile("" : : "r"(temp_v1));
        goto done;

    secondCheck:
        if (temp_v1 != 0x21) {
            goto done;
        }

        D_800774C4 = 1;
        func_8005A840(D_8007D38C);
        goto done;
    }

    if (D_80077484 != 0) {
        if (D_80077978 != 0) {
            func_8005A674(D_80077978);
            func_8005A840((u8*)D_80077978 + 0x5C);
        }

        if (D_800779A8 != 0) {
            func_8005A604(D_800779A8);
        }

        D_80077488 = func_80055194();
        D_800778FC = 1;
        D_80077484 = 0;
    }

done:
    return;
}
