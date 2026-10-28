// SPDX-License-Identifier: AGPL-3.0-or-later

#include "types.h"
#include "functions.h"

// Returns whether the first 12 characters of `a` and `b` are equal.
s32 func_800628C0(char* a, char* b) { return func_80062F58(a, b, 12) == 0; }
