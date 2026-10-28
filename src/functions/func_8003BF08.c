// SPDX-License-Identifier: AGPL-3.0-or-later

#include "types.h"
#include "functions.h"
#include "globals.h"

// Reads a signed byte from the D_8007782C stream.
s8 func_8003BF08(void) { return *D_8007782C++; }
