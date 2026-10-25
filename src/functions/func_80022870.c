// SPDX-License-Identifier: AGPL-3.0-or-later

#include "types.h"

// Approximate length of the vector (arg0, arg1): max(|x|, |y|) +
// min(|x|, |y|) / 2.
s32 func_80022870(s32 arg0, s32 arg1) {
    if (arg0 < 0) {
        arg0 = -arg0;
    }
    if (arg1 < 0) {
        arg1 = -arg1;
    }
    // A conditional expression keeps the "then" arm on the fall-through path
    // like the ROM; an if/else inverts the branch.
    return (arg0 < arg1) ? arg1 + (arg0 >> 1) : arg0 + (arg1 >> 1);
}
