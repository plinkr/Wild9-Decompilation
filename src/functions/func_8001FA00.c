// SPDX-License-Identifier: AGPL-3.0-or-later

#include "types.h"
#include "globals.h"

// Returns the node `index` steps past the head of D_80077968, or NULL if the
// list ends first.
D_80077968_Node* func_8001FA00(s32 index) {
    D_80077968_Node* node = D_80077968;

    // The counter must be the parameter itself: a separate copy makes GCC
    // emit a guard before the loop that the ROM lacks.
    while (index-- != 0 && node != NULL) {
        node = node->next;
    }

    return node;
}
