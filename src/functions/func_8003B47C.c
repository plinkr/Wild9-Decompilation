// SPDX-License-Identifier: AGPL-3.0-or-later

#include "types.h"
#include "functions.h"
#include "globals.h"

// Stores D_8007755C in the table slot selected by a stream byte.
s32 func_8003B47C(void* arg0) {
    u8 index = *D_8007782C;

    D_8007782C++;
    M2C_FIELD((u8*)arg0 + (index << 2), s32*, 8) = D_8007755C;
    return 1;
}
