// SPDX-License-Identifier: AGPL-3.0-or-later

#include "types.h"
#include "functions.h"
#include "globals.h"

// Same as func_8003395C, but the value is the word selected by a stream byte
// in the table at arg0 + 8.
s32 func_800339A0(void* arg0) {
    u8 index = *D_8007782C;
    void* target;

    D_8007782C++;
    target = M2C_FIELD(M2C_FIELD(arg0, void**, 0x44), void**, 0x10);
    func_80033908(
        (u8*)target + 0x190, M2C_FIELD((u8*)arg0 + (index << 2), s32*, 8));
    return 1;
}
