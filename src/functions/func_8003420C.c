// SPDX-License-Identifier: AGPL-3.0-or-later

#include "types.h"
#include "functions.h"
#include "globals.h"

// Resumes the D_8007782C stream at the position saved at +0x60, if any.
s32 func_8003420C(void* arg0) {
    u8* saved = M2C_FIELD(arg0, u8**, 0x60);

    if (saved == NULL) {
        D_8007782C = NULL;
        return 0;
    }
    D_8007782C = saved;
    M2C_FIELD(arg0, u8**, 0x60) = NULL;
    return 1;
}
