// SPDX-License-Identifier: AGPL-3.0-or-later
// https://decomp.me/scratch/wVaJG

#include "types.h"
#include "functions.h"
#include "globals.h"
#include "include_asm.h"
#include "decomp.h"

#define NODE_SIZE 0x18

#define MAGIC_140010 0x140010
#define MAGIC_140130 0x140130
#define MAGIC_E00130 0xE00130
#define MAGIC_E00010 0xE00010
#define MAGIC_55555555 0x55555555
#define MAGIC_8080 0x8080
#define MAGIC_48 0x48
#define OR_MASK 0x05000000
#define PTR_MASK 0xFFFFFF

void func_80010254(void) {
    u8* node;
    register u32 magic_140010 asm("t1");
    register u32 magic_140130 asm("v0");
    register u32 magic_E00130 asm("t0");
    register u32 magic_55555555 asm("t2");
    register u32 ptr_mask asm("a0");
    register u32 magic_E00010 asm("t3");
    register u32 magic_8080 asm("a3");
    register u32 magic_48 asm("a2");
    register u32 or_mask asm("a1");
    register Global* global asm("v1");

    node = func_8001E920(2 * NODE_SIZE);
    if (node != 0) {
        func_8001EBF8(node);

        magic_140010 = MAGIC_140010;
        magic_140130 = MAGIC_140130;
        magic_E00130 = MAGIC_E00130;
        magic_55555555 = MAGIC_55555555;
        ptr_mask = PTR_MASK;
        magic_E00010 = 0xE00000;
        magic_8080 = MAGIC_8080;
        magic_48 = MAGIC_48;

        *(u32*)(node + 8) = magic_140010;
        *(u32*)(node + 0xC) = magic_140130;
        *(u32*)(node + 0x10) = magic_E00130;
        *(u32*)(node + 4) = magic_8080;
        *(u8*)(node + 7) = magic_48;

        global = D_800779A4;
        magic_E00010 |= 0x10;
        *(u32*)(node + 0x14) = magic_55555555;

        magic_140130 = global->unk28;
        or_mask = OR_MASK;
        magic_140130 |= or_mask;
        *(u32*)(node + 0) = magic_140130;

        magic_140130 = (u32)node & ptr_mask;
        node += NODE_SIZE;
        global->unk28 = magic_140130;

        *(u32*)(node + 8) = magic_140010;
        *(u32*)(node + 0xC) = magic_E00010;
        *(u32*)(node + 0x10) = magic_E00130;
        *(u32*)(node + 4) = magic_8080;
        *(u8*)(node + 7) = magic_48;

        global = D_800779A4;
        *(u32*)(node + 0x14) = magic_55555555;

        magic_140130 = global->unk28;
        ptr_mask = (u32)node & ptr_mask;
        magic_140130 |= or_mask;
        *(u32*)(node + 0) = magic_140130;
        global->unk28 = ptr_mask;
    }
}
