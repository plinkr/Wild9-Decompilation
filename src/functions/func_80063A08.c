// SPDX-License-Identifier: AGPL-3.0-or-later

#include "types.h"
#include "functions.h"
#include "globals.h"

/**
 * Starts a transfer: func_80063C48(1, arg1, arg2), stores bit 0 of `mode` in
 * D_8007B2E4 and the two callbacks in D_8007C210/D_8007C214, and clears the
 * progress state.
 */
void func_80063A08(s32 mode, s32 arg1, s32 arg2, void* callback, void* arg4) {
    func_80063C48(1, arg1, arg2);
    D_80080F20 = 0;
    D_8007C210 = callback;
    D_8007B2E4 = mode & 1;
    D_8007D240 = 0;
    D_8007CDC0 = 0;
    D_8007B2E0 = 0;
    D_8007AFA0 = 0;
    D_8007C214 = arg4;
    // !FAKE: keeps the epilogue restores from being scheduled between the
    // stores, as in the original.
    __asm__ volatile("");
}
