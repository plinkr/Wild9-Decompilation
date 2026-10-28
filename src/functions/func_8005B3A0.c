// SPDX-License-Identifier: AGPL-3.0-or-later

#include "types.h"
#include "functions.h"
#include "globals.h"

// Builds a GPU draw mode command (0xE1).
u32 func_8005B3A0(s32 dither, s32 draw_on_display, s32 tpage) {
    // !FAKE: pinning both halves reproduces the ROM register choice.
    register u32 command asm("v1") = 0xE1000000;
    register u32 mode asm("v0");

    if (draw_on_display != 0) {
        command |= 0x200;
    }
    mode = tpage & 0x9FF;
    if (dither != 0) {
        mode |= 0x400;
    }
    return command | mode;
}
