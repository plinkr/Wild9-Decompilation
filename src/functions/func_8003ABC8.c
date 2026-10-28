// SPDX-License-Identifier: AGPL-3.0-or-later

#include "types.h"
#include "functions.h"
#include "globals.h"

s32 func_8003ABC8(void* arg0) {
    func_80053E6C(M2C_FIELD(arg0, s32*, 0x18), &M2C_FIELD(arg0, s32*, 0x18),
                  &M2C_FIELD(arg0, s32*, 0x1C));
    return 1;
}
