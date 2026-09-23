// SPDX-License-Identifier: AGPL-3.0-or-later

#ifndef WILD9_DECOMP_H
#define WILD9_DECOMP_H

#include "types.h"

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8*)(expr) + (offset)))

typedef struct {
    u32 w0;
    u32 w1;
    u32 w2;
    u32 w3;
    u32 w4;
    u32 w5;
    u32 w6;
    u32 w7;
    u32 w8;
    u32 w9;
    u32 w10;
    u32 w11;
    u32 w12;
    u32 w13;
    u32 w14;
    u32 w15;
} W9Copy64;

typedef struct {
    u16 unk0;     /* 0x00 */
    u16 unk2;     /* 0x02 */
    u16 unk4;     /* 0x04 */
    u16 unk6;     /* 0x06 */
    u16 unk8;     /* 0x08 */
    u16 unkA;     /* 0x0A */
    u16 unkC;     /* 0x0C */
    u16 unkE;     /* 0x0E */
    u16 unk10;    /* 0x10 */
    u16 unk12;    /* 0x12 */
    u16 unk14[2]; /* 0x14 */
    u16 unk18;    /* 0x18 */
    u16 unk1A;    /* 0x1A */
    u16 unk1C;    /* 0x1C */
    u16 unk1E;    /* 0x1E */
    u16 unk20;    /* 0x20 */
    u16 unk22;    /* 0x22 */
    u16 unk24;    /* 0x24 */
    u16 unk26;    /* 0x26 */
    u16 unk28;    /* 0x28 */
    u16 unk2A;    /* 0x2A */
} UnkStruct;

typedef struct Global {
    u8 pad[0x28];
    u32 unk28;
} Global;

#endif
