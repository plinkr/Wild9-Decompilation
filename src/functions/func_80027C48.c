// SPDX-License-Identifier: AGPL-3.0-or-later

#include "types.h"
#include "globals.h"

// Unlinks `node` from the active list (head D_800779A0) and pushes it onto
// the free list (D_80077980).
void func_80027C48(D_80077B14_Node* node) {
    D_80077B14_Node* prev;
    D_80077B14_Node* next;

    if (node == NULL) {
        return;
    }
    D_80077904--;
    prev = node->prev;
    next = node->next;
    if (prev != NULL) {
        prev->next = next;
    }
    if (next != NULL) {
        next->prev = prev;
    }
    if (D_800779A0 == node) {
        D_800779A0 = next;
    }
    node->next = D_80077980;
    D_80077980 = node;
}
