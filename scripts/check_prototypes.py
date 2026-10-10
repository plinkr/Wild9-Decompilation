#!/usr/bin/env python3
"""Check that prototypes in a shared header agree with the C definitions."""

from __future__ import annotations

import argparse
import re
import sys
from pathlib import Path

FUNC_RE = re.compile(r"\bfunc_[0-9A-Fa-f]{8}\b")
COMMENT_RE = re.compile(r"/\*.*?\*/|//[^\n]*", re.S)
STORAGE_RE = re.compile(r"\b(?:register|const|volatile|static|inline)\b")
IDENT_RE = re.compile(r"[A-Za-z_][A-Za-z0-9_]*")
TYPE_KEYWORDS = {
    "void", "int", "char", "long", "short", "signed", "unsigned",
    "float", "double", "struct", "union", "enum", "_Bool",
}
C_INCLUDE_RE = re.compile(r'^[ \t]*#include\s+"functions/([A-Za-z_][A-Za-z0-9_]*)\.c"[ \t]*$', re.M)


class Decl:
    __slots__ = ("name", "ret", "args", "path", "line")

    def __init__(self, name: str, ret: str, args: str, path: str, line: int) -> None:
        self.name = name
        self.ret = ret
        self.args = args
        self.path = path
        self.line = line

    def render(self) -> str:
        params = normalise_params(self.args)
        return "%s %s(%s)" % (self.ret, self.name, ", ".join(params) if params else "void")

    def signature(self) -> tuple[str, tuple[str, ...]]:
        return (canon_type(self.ret), normalise_params(self.args))


def strip_comments(text: str) -> str:
    return COMMENT_RE.sub(lambda m: " " * len(m.group(0)), text)


def canon_type(text: str) -> str:
    t = re.sub(r"\[[^\]]*\]", "", text)
    t = re.sub(r"\basm\s*\(.*?\)", " ", t, flags=re.S)
    t = STORAGE_RE.sub(" ", t)
    return re.sub(r"\s+", "", t)


NAME_ONLY = re.compile(r"^(\*+)([A-Za-z_][A-Za-z0-9_]*)$")
TAG_KEYWORDS = {"struct", "union", "enum"}


def drop_param_name(param: str) -> str:
    text = re.sub(r"\[[^\]]*\]", " ", param)
    text = re.sub(r"\basm\s*\(.*?\)", " ", text, flags=re.S)
    text = STORAGE_RE.sub(" ", text)
    tokens = text.split()
    if len(tokens) < 2:
        return text

    last = tokens[-1]

    m = NAME_ONLY.match(last)
    if m:
        return " ".join(tokens[:-1] + [m.group(1)])

    if len(tokens) == 2 and tokens[-2] in TAG_KEYWORDS:
        return text

    if IDENT_RE.fullmatch(last) and last not in TYPE_KEYWORDS:
        return " ".join(tokens[:-1])

    return text


def split_top_level(text: str) -> list[str]:
    out, depth, cur = [], 0, []
    for ch in text:
        if ch in "([":
            depth += 1
        elif ch in ")]":
            depth -= 1
        if ch == "," and depth == 0:
            out.append("".join(cur))
            cur = []
        else:
            cur.append(ch)
    if "".join(cur).strip():
        out.append("".join(cur))
    return [x.strip() for x in out if x.strip()]


def normalise_params(args: str) -> tuple[str, ...]:
    a = args.strip()
    if not a or a == "void":
        return ()
    return tuple(canon_type(drop_param_name(p)) for p in split_top_level(a))


def scan_calls(text: str) -> list[tuple[str, str, str, int, int]]:
    out = []
    for m in FUNC_RE.finditer(text):
        i = m.end()
        while i < len(text) and text[i] in " \t":
            i += 1
        if i >= len(text) or text[i] != "(":
            continue
        depth, j = 0, i
        while j < len(text):
            if text[j] == "(":
                depth += 1
            elif text[j] == ")":
                depth -= 1
                if depth == 0:
                    break
            j += 1
        if j >= len(text):
            continue
        head = text[text.rfind("\n", 0, m.start()) + 1 : m.start()]
        out.append((head, m.group(0), text[i + 1 : j], text.count("\n", 0, m.start()) + 1, j + 1))
    return out


def prototypes_from_header(path: Path) -> list[Decl]:
    text = strip_comments(path.read_text())
    decls = []
    for head, name, args, line, end in scan_calls(text):
        tail = text[end:]
        if not tail.lstrip(" \t\r\n").startswith(";"):
            continue
        decls.append(Decl(name, head.strip() or "int", args, str(path), line))
    return decls


def definitions_from_source(path: Path) -> list[Decl]:
    text = strip_comments(path.read_text())
    decls = []
    for head, name, args, line, end in scan_calls(text):
        if text[end : end + 40].lstrip(" \t\r\n")[:1] != "{":
            continue
        decls.append(Decl(name, head.strip() or "int", args, str(path), line))
    return decls


def main() -> int:
    ap = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter
    )
    ap.add_argument("--header", action="append", default=[],
                    help="header to check (default: include/functions.h)")
    ap.add_argument("--source-dir", default="src/functions",
                    help="directory holding the promoted function .c files")
    ap.add_argument("--main-c", default="src/main.c",
                    help="manifest listing which functions are promoted")
    ap.add_argument("--function", default=None,
                    help="only report conflicts involving this function")
    ap.add_argument("--warnings-as-errors", action="store_true",
                    help="also fail on conflicts in not-yet-promoted functions")
    ap.add_argument("--quiet", action="store_true", help="suppress the summary")
    args = ap.parse_args()

    headers = [Path(h) for h in (args.header or ["include/functions.h"])]
    src = Path(args.source_dir)

    promoted: set[str] = set()
    main_c = Path(args.main_c)
    if main_c.is_file():
        promoted = set(C_INCLUDE_RE.findall(main_c.read_text()))

    protos: dict[str, list[Decl]] = {}
    for h in headers:
        for d in prototypes_from_header(h):
            protos.setdefault(d.name, []).append(d)

    defs: dict[str, list[Decl]] = {}
    n_defs = 0
    for c in sorted(src.glob("*.c")):
        for d in definitions_from_source(c):
            defs.setdefault(d.name, []).append(d)
            n_defs += 1

    errors: list[str] = []
    warnings: list[str] = []
    for name in sorted(set(protos) & set(defs)):
        if args.function and name != args.function:
            continue
        for p in protos[name]:
            for d in defs[name]:
                if p.signature() == d.signature():
                    continue
                msg = ("%s:%d: prototype `%s` conflicts with definition `%s` in %s:%d"
                       % (p.path, p.line, p.render(), d.render(), d.path, d.line))
                (errors if name in promoted else warnings).append(msg)

    for e in errors:
        print("error: " + e, file=sys.stderr)
    for w in warnings:
        print("warning: %s (not promoted into %s yet)"
              % (w, main_c), file=sys.stderr)

    if not args.quiet:
        print("promoted=%d definitions=%d prototypes=%d checked=%d errors=%d warnings=%d"
              % (len(promoted), n_defs, len(protos), len(set(protos) & set(defs)),
                 len(errors), len(warnings)))
    return 1 if (errors or (warnings and args.warnings_as_errors)) else 0


if __name__ == "__main__":
    raise SystemExit(main())