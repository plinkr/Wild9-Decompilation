// SPDX-License-Identifier: AGPL-3.0-or-later

#include "types.h"
#include "functions.h"

// Dispatches on the sign of arg1 and arg2: a negative value means that
// argument is not used.
void func_8002A13C(void* arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (arg1 < 0) {
        func_8002A18C(arg0, arg2, arg3);
    } else if (arg2 >= 0) {
        func_8002A5A4(arg0, arg1, arg2, arg3);
    } else {
        func_8002A2F4(arg0, arg1);
    }
}
