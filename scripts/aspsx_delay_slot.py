#!/usr/bin/env python3

"""Restores ASPSX bare macro store delay-slot expansion for matching functions.

GCC 2.8.1-PSX leaves unconditional jump delay slots empty when preceded by a
bare symbol store macro. ASPSX expanded such stores by hoisting lui $at,%hi(sym)
before the jump and placing the store in the delay slot. maspsx and GNU as do
not replicate this, causing binary mismatches.

Rewrites are gated against reference assembly to prevent modifying functions
whose stores genuinely belong outside delay slots.
"""

from __future__ import annotations

import re
from collections import Counter

# Longest first so "sd" does not shadow "sdl"/"sdc1" in regex matching.
STORE_OPERANDS = (
    "swc1",
    "swc2",
    "sdc1",
    "swl",
    "swr",
    "sdl",
    "sdr",
    "sw",
    "sh",
    "sb",
    "sd",
)

_STORE_PATTERN = "|".join(STORE_OPERANDS)

CANDIDATE_STORE_RE = re.compile(
    r"^(?P<indent>[ \t]*)(?P<op>" + _STORE_PATTERN + r")"
    r"[ \t]+(?P<reg>\$\w+)[ \t]*,[ \t]*"
    r"(?P<sym>[A-Za-z_][A-Za-z0-9_]*)[ \t]*$"
)

JUMP_RE = re.compile(
    r"^[ \t]*(?P<op>j|jr)[ \t]+"
    r"(?P<target>\$\w+|\.?[A-Za-z_][A-Za-z0-9_]*)[ \t]*$"
)

BRANCH_DEBUG_NOP_RE = re.compile(
    r"^[ \t]*nop[ \t]*#[ \t]*DEBUG:[ \t]*branch/jump[ \t]*$"
)

REFERENCE_STORE_RE = re.compile(
    r"^[ \t]*/\*[^*]*\*/"
    r"(?P<gap>[ \t]+)(?P<op>" + _STORE_PATTERN + r")"
    r"[ \t]+(?P<reg>\$\w+)[ \t]*,[ \t]*"
    r"%lo\((?P<sym>[A-Za-z_][A-Za-z0-9_]*)\)\(\$at\)[ \t]*$"
)

SET_AT_RE = re.compile(r"^[ \t]*\.set[ \t]+(?P<state>at|noat)[ \t]*$")

ENT_RE = re.compile(r"^[ \t]*\.ent[ \t]+(?P<name>[A-Za-z_][A-Za-z0-9_]*)[ \t]*$")

END_RE = re.compile(r"^[ \t]*\.end[ \t]+(?P<name>[A-Za-z_][A-Za-z0-9_]*)[ \t]*$")

LABEL_RE = re.compile(r"^\s*([A-Za-z_][A-Za-z0-9_]*)\s*:\s*$")

_REGISTER_NUMBERS = {
    "zero": 0,
    "at": 1,
    "v0": 2,
    "v1": 3,
    "a0": 4,
    "a1": 5,
    "a2": 6,
    "a3": 7,
    "t0": 8,
    "t1": 9,
    "t2": 10,
    "t3": 11,
    "t4": 12,
    "t5": 13,
    "t6": 14,
    "t7": 15,
    "s0": 16,
    "s1": 17,
    "s2": 18,
    "s3": 19,
    "s4": 20,
    "s5": 21,
    "s6": 22,
    "s7": 23,
    "t8": 24,
    "t9": 25,
    "k0": 26,
    "k1": 27,
    "gp": 28,
    "sp": 29,
    "fp": 30,
    "s8": 30,
    "ra": 31,
}


def register_number(register: str) -> int | None:
    """Normalize register names and numbers to indices for matching."""
    text = register.lstrip("$")

    if text.isdigit():
        return int(text)

    return _REGISTER_NUMBERS.get(text.lower())


def read_function(text: str, function: str) -> str:
    """Extract a function slice from reference assembly for validation."""

    patterns = [
        re.compile(
            rf"^\s*glabel\s+{re.escape(function)}\s*$",
            re.MULTILINE,
        ),
        re.compile(
            rf"^\s*{re.escape(function)}\s*:\s*$",
            re.MULTILINE,
        ),
    ]

    start_match = None

    for pattern in patterns:
        start_match = pattern.search(text)

        if start_match:
            break

    if start_match is None:
        raise RuntimeError(f"Could not find {function} in reference assembly")

    start = start_match.end()

    end_match = re.search(
        r"^\s*endlabel\b",
        text[start:],
        re.MULTILINE,
    )

    if end_match:
        return text[start : start + end_match.start()]

    next_function = re.search(
        r"^\s*glabel\s+[A-Za-z_][A-Za-z0-9_]*\s*$",
        text[start:],
        re.MULTILINE,
    )

    if next_function:
        return text[start : start + next_function.start()]

    return text[start:]


def delay_slot_stores(reference_body: str) -> tuple[Counter, Counter]:
    """Identify reference $at stores, using disassembler indentation to detect delay slots."""
    slot: Counter = Counter()
    plain: Counter = Counter()

    for line in reference_body.splitlines():
        match = REFERENCE_STORE_RE.match(line)

        if match is None:
            continue

        register = register_number(match.group("reg"))

        if register is None:
            continue

        key = (match.group("op"), register, match.group("sym"))

        if len(match.group("gap")) >= 3:
            slot[key] += 1
        else:
            plain[key] += 1

    return slot, plain


def rewrite(text: str, reference_body: str) -> tuple[str, int]:
    """Move bare macro stores into jump delay slots when reference assembly confirms it."""

    slot_stores, plain_stores = delay_slot_stores(reference_body)

    lines = text.splitlines()

    sites: list[dict] = []
    noat = False

    for index, line in enumerate(lines):
        set_match = SET_AT_RE.match(line)

        if set_match is not None:
            noat = set_match.group("state") == "noat"
            continue

        match = CANDIDATE_STORE_RE.match(line)

        if match is None:
            continue

        jump_index = index + 1

        while jump_index < len(lines) and (
            lines[jump_index].strip() == ""
            or lines[jump_index].lstrip().startswith("#")
        ):
            jump_index += 1

        if jump_index >= len(lines) or JUMP_RE.match(lines[jump_index]) is None:
            continue

        if (
            jump_index + 1 >= len(lines)
            or BRANCH_DEBUG_NOP_RE.match(lines[jump_index + 1]) is None
        ):
            continue

        register = register_number(match.group("reg"))

        if register is None:
            continue

        sites.append(
            {
                "store_index": index,
                "jump_index": jump_index,
                "nop_index": jump_index + 1,
                "indent": match.group("indent"),
                "op": match.group("op"),
                "reg": match.group("reg"),
                "sym": match.group("sym"),
                "key": (match.group("op"), register, match.group("sym")),
                "noat": noat,
            }
        )

    by_key: dict[tuple, list[dict]] = {}

    for site in sites:
        by_key.setdefault(site["key"], []).append(site)

    accepted: list[dict] = []

    for key, group in by_key.items():
        # The reference must prove that this store is executed inside a
        # delay slot, and it must be the only shape for this key.
        if key not in slot_stores or key in plain_stores:
            continue

        if len(group) != slot_stores[key]:
            continue

        accepted.extend(group)

    if not accepted:
        return text, 0

    remove_indices = {site["store_index"] for site in accepted}

    insert_map: dict[int, list[dict]] = {}
    replace_map: dict[int, dict] = {}

    for site in accepted:
        insert_map.setdefault(site["jump_index"], []).append(site)
        replace_map[site["nop_index"]] = site

    result: list[str] = []

    for index, line in enumerate(lines):
        for site in insert_map.get(index, []):
            # Explicit $at use belongs inside a .set noat region so the
            # assembler never claims $at for a macro expansion.
            if not site["noat"]:
                result.append("\t.set\tnoat")

            result.append(f"{site['indent']}lui\t$at,%hi({site['sym']})")

        if index in remove_indices:
            continue

        site = replace_map.get(index)

        if site is not None:
            result.append(
                f"{site['indent']}{site['op']}\t{site['reg']},%lo({site['sym']})($at)"
            )

            if not site["noat"]:
                result.append("\t.set\tat")

            continue

        result.append(line)

    return "\n".join(result) + "\n", len(accepted)


def rewrite_translation_unit(text: str, reference_text: str) -> tuple[str, int]:
    """Apply delay-slot rewriting across every function in a translation unit."""

    lines = text.splitlines()

    result: list[str] = []
    moved = 0

    index = 0

    while index < len(lines):
        ent_match = ENT_RE.match(lines[index])

        if ent_match is None:
            result.append(lines[index])
            index += 1
            continue

        name = ent_match.group("name")

        end_index = index + 1

        while end_index < len(lines) and END_RE.match(lines[end_index]) is None:
            end_index += 1

        if end_index >= len(lines):
            result.append(lines[index])
            index += 1
            continue

        block = "\n".join(lines[index : end_index + 1]) + "\n"

        try:
            reference_body = read_function(reference_text, name)
        except RuntimeError:
            result.append(block.rstrip("\n"))
            index = end_index + 1
            continue

        rewritten, count = rewrite(block, reference_body)

        result.append(rewritten.rstrip("\n"))
        moved += count

        index = end_index + 1

    return "\n".join(result) + "\n", moved
