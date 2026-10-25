// SPDX-License-Identifier: AGPL-3.0-or-later

#include "globals.h"

// Appends a node to the singly linked list D_80077968 (head) / D_8007798C
// (tail).
void func_8001F9D0(D_80077968_Node* node) {
    if (D_80077968 == NULL) {
        D_80077968 = node;
        D_8007798C = node;
        node->next = NULL;
    } else {
        D_8007798C->next = node;
        D_8007798C = node;
    }
}
