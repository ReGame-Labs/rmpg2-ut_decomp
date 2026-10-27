#!/usr/bin/env python3
"""The matching loop's scorer: put C in place of a function in its unit, score variants of it, brute-force the order
of marked lines. Every candidate is compiled with its whole unit, as build.ninja compiles it (the compiler and -G
of configure.py's CC_OVERRIDES/G_OVERRIDES, through tools/cc_psx.sh), from a copy under build/variant/, and checked
by tools/unit_diff.py's comparison: the words as the link writes them. A candidate is a match only when the
function passes and the whole unit links to the original bytes (unit_diff's exit 0). The unit's file is written
only when a candidate is kept, and a kept candidate is checked first: as C it must match; as a WIP the unit must
still link and the block must compile with -DNON_MATCHING. No ninja: other sessions can build meanwhile.

  tools/venv/bin/python tools/variant.py get  <func>           the function's C (a WIP's C); INCLUDE_ASM: nothing
  tools/venv/bin/python tools/variant.py put  <func> <file|->  put the file's C in place of the function (its
                                                     INCLUDE_ASM, its C or its WIP block), score it; kept
                                                     if it matches
  tools/venv/bin/python tools/variant.py try  <func> <file>    score the variants (separated by `//---` lines), ranked
  tools/venv/bin/python tools/variant.py perm <func> <file>    score every order of the `//@P` lines and every choice
                                                     of the `//@G<name>` alternatives (--max N, 5040; sampled beyond);
                                                     the best goes to build/variant/<target>/<unit>/<func>.best.c

  -k [N]                try: keep variant N (the best without N); perm: keep the best
  --wip [--note TEXT]   keep a candidate that does not match as `#ifdef NON_MATCHING` C with the INCLUDE_ASM in the
                        `#else` and its score in a comment (the note: TEXT, else the block's old note, else what
                        unit_diff says differs)
  -s [-C N]             the candidate's instructions (put; try, perm: the kept or the best) and the original's, aligned
                        (difflib) side by side: branch targets compared through the alignment, relocated fields as
                        linked, so a shift is no difference; N lines of context around the differences (3, -1 all)
  --dump [SECTIONS]     cc1's register allocation of the candidate (put; try, perm: the kept or the best; get: the
                        unit's C) from its -dl/-dg dumps: each pseudo's refs, live length, priority, allocation order
                        and hard register, the variables' registers (-g); SECTIONS (`L`, `c`, `lg`, `loop,combine`)
                        also prints those dumps' text of the function (l lreg, g greg, L loop, c combine, s cse, t cse2,
                        f flow, j jump, J jump2, S sched, R sched2, d dbr, r rtl, F addressof)
  -t TARGET, -u UNIT    where the function is (default: found under src/); -j N parallel compiles (RMPG2_JOBS, 4)
  -V VER, -G N, -D DEF  as tools/unit_diff.py (nothing is kept with -D)

A replacement is the function's definition, ANSI or K&R, optionally with declarations before it (they move with
it; those the unit already has before the function are left out, so putting a function twice does not repeat them).
Markers (perm), on a line of their own or at the end of a statement's line:
      //@P a->x = 0;          a line of the permuted set P (`//@P2 ...` another set, permuted independently)
      a->y = 0; //@P          the same, the line compilable as it is
      //@G1 n = 3 - x;        alternatives of group G1: one is kept, the others dropped
      //@G1                   an empty alternative: none of the group's lines
"""
import argparse
import difflib
import functools
import math
import os
import random
import re
import subprocess
import sys
import textwrap
from concurrent.futures import ThreadPoolExecutor, as_completed
from dataclasses import dataclass, field
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "tools"))
import unit_diff  # noqa: E402
from unit_diff import configure  # noqa: E402

# ---- the function's place in its unit -----------------------------------------------------------------------------


def skip_literal(text: str, i: int) -> int:
    """The index after the string or character literal starting at i."""
    q, i = text[i], i + 1
    while i < len(text) and text[i] != q:
        i += 2 if text[i] == "\\" else 1
    return i + 1


def skip_balanced(text: str, i: int) -> int:
    """The index after the bracket at i and its partner; literals and comments skipped."""
    pairs = {"(": ")", "[": "]", "{": "}"}
    stack, n = [], len(text)
    while i < n:
        c = text[i]
        if text.startswith("/*", i):
            i = text.find("*/", i + 2)
            i = n if i < 0 else i + 2
            continue
        if text.startswith("//", i):
            i = text.find("\n", i)
            i = n if i < 0 else i
            continue
        if c in "\"'":
            i = skip_literal(text, i)
            continue
        if c in pairs:
            stack.append(pairs[c])
        elif stack and c == stack[-1]:
            stack.pop()
            if not stack:
                return i + 1
        i += 1
    raise ValueError("unbalanced brackets")


def skip_space(text: str, i: int) -> int:
    """The index of the next character that is not white space or a comment."""
    n = len(text)
    while i < n:
        if text[i].isspace():
            i += 1
        elif text.startswith("/*", i):
            j = text.find("*/", i + 2)
            i = n if j < 0 else j + 2
        elif text.startswith("//", i):
            j = text.find("\n", i)
            i = n if j < 0 else j
        else:
            break
    return i


def definition_end(text: str, paren: int):
    """For a declarator's parameter list at `paren`: the index after the definition's closing brace and its newline,
    None when it is a declaration. A K&R definition's parameter declarations sit between the list and the body."""
    try:
        i = skip_space(text, skip_balanced(text, paren))
    except ValueError:
        return None
    if i >= len(text):
        return None
    if text[i] != "{":
        if not (text[i].isalpha() or text[i] == "_"):
            return None  # a prototype, a declaration list, an initializer
        k = text.find("{", i)
        if k < 0 or not text[i:k].rstrip().endswith(";"):
            return None
        i = k
    end = skip_balanced(text, i)
    return end + 1 if text.startswith("\n", end) else end


SCORE_NOTE = re.compile(r"/\*\s*(?:~?\d+(?:\.\d+)?\s*%|\d+ instructions? differ)")


def note_of(comment: str) -> str:
    """A score comment's note: its text after the score, the comment markers and line breaks removed."""
    body = re.sub(r"^\s*/\*|\*/\s*$", "", comment.strip())
    body = " ".join(ln.strip().lstrip("*").strip() for ln in body.splitlines())
    m = re.match(r"\s*(?:~?\d+(?:\.\d+)?\s*%|\d+ instructions? differ)\s*:?\s*(.*)$", body, re.S)
    return (m.group(1) if m else body).strip()


@dataclass
class Region:
    """A function's text in its unit: [start, end) of the unit's text."""
    start: int
    end: int
    kind: str           # "asm" (an INCLUDE_ASM line), "c" (a definition), "wip" (a NON_MATCHING block)
    c: str = None       # the C (a WIP block's C, without its score comment)
    note: str = None    # a WIP's old note
    folder: str = None  # the INCLUDE_ASM's folder
    func: str = None    # the function's name


def enclosing_if(text: str, pos: int):
    """The start of the `#if` line that the preprocessor line at `pos` (an #else) belongs to."""
    depth, i = 0, pos
    while i > 0:
        j = text.rfind("\n", 0, i - 1) + 1
        line = text[j:i].strip()
        if line.startswith("#endif"):
            depth += 1
        elif line.startswith("#if"):
            if depth == 0:
                return j
            depth -= 1
        i = j
    return None


def find(text: str, func: str):
    """The function's Region in a unit's text, or None."""
    f = re.escape(func)
    m = re.search(rf'^INCLUDE_ASM\(\s*"([^"]+)"\s*,\s*{f}\s*\);[^\n]*(?:\n|$)', text, re.M)
    if m:
        folder = m.group(1)
        before = text[:m.start()]
        em = re.match(r"[ \t]*#[ \t]*endif[^\n]*(?:\n|$)", text[m.end():])
        if re.search(r"(?:^|\n)[ \t]*#[ \t]*else[^\n]*\n$", before) and em:
            else_at = before.rstrip("\n").rfind("\n") + 1
            start = enclosing_if(text, else_at)
            head = text[start:text.index("\n", start)] if start is not None else ""
            if re.match(r"\s*#\s*(?:ifdef\s+NON_MATCHING|if\s+defined\s*\(?\s*NON_MATCHING)\b", head):
                body = text[text.index("\n", start) + 1:else_at]
                note = None
                cm = re.match(r"\s*(/\*.*?\*/)[ \t]*\n", body, re.S)
                if cm and SCORE_NOTE.match(cm.group(1)):
                    note, body = note_of(cm.group(1)), body[cm.end():]
                above = re.search(r"(?:^|\n)(/\*(?:(?!\*/).)*\*/[ \t]*\n)$", text[:start], re.S)
                if above and SCORE_NOTE.match(above.group(1)):
                    note = note or note_of(above.group(1))
                    start -= len(above.group(1))
                return Region(start, m.end() + em.end(), "wip", body.strip("\n") + "\n", note, folder, func)
        return Region(m.start(), m.end(), "asm", None, None, folder, func)
    for m in re.finditer(rf"^[A-Za-z_][^\n;{{}}=]*?\b{f}\s*\(", text, re.M):
        end = definition_end(text, m.end() - 1)
        if end:
            return Region(m.start(), end, "c", text[m.start():end], func=func)
    return None


def code_of(text: str) -> str:
    """The text without its comments, its white space collapsed: a declaration's identity."""
    out, i, n = [], 0, len(text)
    while i < n:
        if text.startswith("/*", i):
            j = text.find("*/", i + 2)
            i = n if j < 0 else j + 2
            out.append(" ")
        elif text.startswith("//", i):
            j = text.find("\n", i)
            i = n if j < 0 else j
        elif text[i] in "\"'":
            j = skip_literal(text, i)
            out.append(text[i:j])
            i = j
        else:
            out.append(text[i])
            i += 1
    return " ".join("".join(out).split())


def items(text: str) -> list:
    """The text cut into its top-level items, [(text, key)], the texts joined being the text: a declaration up to its
    `;` (key: its code_of), a preprocessor line (key: the same), a function definition up to its body's brace (key:
    None); the comments and blank lines before an item go with it, a comment after it on its line too."""
    out, n, start = [], len(text), 0
    while True:
        i = skip_space(text, start)
        if i >= n:
            if start < n:
                out.append((text[start:], None))
            return out
        key = None
        if text[i] == "#" and not text[text.rfind("\n", 0, i) + 1:i].strip():
            j = i
            while True:
                j = text.find("\n", j)
                if j < 0 or text[j - 1] != "\\":
                    break
                j += 1
            end = n if j < 0 else j
            key = code_of(text[i:end])
        else:
            j = i
            try:
                while j < n:
                    c = text[j]
                    if text.startswith("/*", j) or text.startswith("//", j):
                        j = skip_space(text, j)
                    elif c in "\"'":
                        j = skip_literal(text, j)
                    elif c in "([":
                        j = skip_balanced(text, j)
                    elif c == "{":
                        head = code_of(text[i:j])
                        j = skip_balanced(text, j)
                        if not (head.endswith("=") or re.search(r"\b(?:struct|union|enum)(?: \w+)?$", head)):
                            break  # a function's body
                    elif c == ";":
                        j += 1
                        key = code_of(text[i:j])
                        break
                    else:
                        j += 1
            except ValueError:
                j = n
            end = j
        m = re.match(r"[ \t]*(?://[^\n]*)?(?:\n|$)", text[end:])
        end = min(n, end + m.end()) if m else end
        out.append((text[start:end], key))
        start = end


WIP_C = re.compile(r"^[ \t]*#[ \t]*if(?:def[ \t]+|[ \t]+defined[ \t]*\(?[ \t]*)NON_MATCHING\b.*?^[ \t]*#[ \t]*else\b",
                   re.M | re.S)


@functools.lru_cache(maxsize=8)
def known_declarations(text: str) -> frozenset:
    """The keys of the declarations in `text`, outside the WIP blocks' C (once per unit: try and perm put many)."""
    return frozenset(k for _, k in items(WIP_C.sub("", text)) if k)


def new_declarations(unit_text: str, region: Region, c: str) -> str:
    """`c` without the declarations above its definition that the unit already has before the function (outside
    the WIP blocks' C), and without a comment the unit already has right above it: putting the same function twice
    does not repeat them."""
    d = find(c, region.func) if region.func else None
    if d is None or d.kind != "c" or d.start == 0:
        return c
    before = unit_text[:region.start]
    known = known_declarations(before)
    head, kept = [], False
    for t, k in items(c[:d.start]):
        if k is not None:
            new = k not in known
            kept |= new
        elif code_of(t):
            new = True
        elif t.strip():  # a comment right above the definition
            new = not before.rstrip().endswith(t.strip())
        else:  # the blank lines after the declarations
            new = kept
        if new:
            head.append(t)
    return "".join(head) + c[d.start:]


def wip_comment(score: str, note: str) -> str:
    text = f"{score}: {note}" if note else score
    lines = textwrap.wrap(text, 113) or [""]
    if len(lines) == 1:
        return f"/* {lines[0]} */"
    return "\n".join(["/* " + lines[0]] + [" * " + ln for ln in lines[1:-1]] + [" * " + lines[-1] + " */"])


def wip_block(c: str, comment: str, folder: str, func: str) -> str:
    return (f"#ifdef NON_MATCHING\n{comment}\n{c.strip(chr(10))}\n#else\n"
            f'INCLUDE_ASM("{folder}", {func});\n#endif\n')


# ---- scoring --------------------------------------------------------------------------------------------------------

@dataclass
class Score:
    error: str = None        # the compiler's complaint
    reasons: list = field(default_factory=list)  # unit_diff's, [] = the function passes
    pct: float = None        # objdiff's match percent
    links: bool = False      # the whole unit links to the original bytes
    unit: list = field(default_factory=list)     # why it does not
    ndiff: int = 0           # words that differ once linked, plus the size difference in words
    mark: str = ""           # the function's result as unit_diff prints it
    obj: Path = None         # the object, when kept for a diff
    res: object = None

    @property
    def match(self) -> bool:
        return self.error is None and not self.reasons and self.links

    def key(self):
        return (self.match, self.error is None and not self.reasons, self.error is None,
                self.pct or 0.0, -self.ndiff)

    def percent(self) -> str:
        if self.error is None and not self.reasons:
            return "100%"
        return "?%" if self.pct is None else f"{math.floor(self.pct * 100) / 100:.2f}%"

    def __str__(self):
        if self.error is not None:
            return "compile error: " + self.error
        if self.match:
            return f"MATCH ({self.mark}, the unit links)"
        if not self.reasons:
            return f"{self.mark}, but the unit does not link: {'; '.join(self.unit)}"
        return self.mark


def compile_errors(log: str) -> str:
    keep = [ln for ln in log.splitlines()
            if ln.strip() and "warning:" not in ln and not re.search(r": (In function|At top level)", ln)]
    return " | ".join(ln.split(": ", 1)[-1] if ".c:" in ln else ln for ln in keep[:3]) or log.strip()[-300:]


class Unit:
    """A C unit and how to compile and check it."""

    def __init__(self, target: str, name: str, path: Path = None, cc: str = None, g: int = None,
                 flags: list = None, checker: unit_diff.Checker = None, work: Path = None):
        self.target, self.name = target, name
        self.path = path or ROOT / f"src/{target}/{name}.c"
        src = f"src/{target}/{name}.c"
        self.cc = cc or configure.CC_OVERRIDES.get(src, configure.DEFAULT_CC)
        self.g = g if g is not None else configure.g_for(src)
        self.flags = flags if flags is not None else [
            *configure.cc_flags(src), *configure.CC_INCLUDES.split(), f"-I{Path(src).parent}"]
        self._checker = checker
        self.work = work or ROOT / "build/variant" / target / name.replace("/", "__")
        self.folder = f"asm/{target}/nonmatchings/{name}"

    @property
    def checker(self) -> unit_diff.Checker:
        if self._checker is None:
            self._checker = unit_diff.Checker(self.target, self.name)
        return self._checker

    def text(self) -> str:
        return self.path.read_text()

    def compile(self, text: str, tag: str, defines=(), includes=(), preprocess=False, cc1=()):
        """Compile `text` as this unit: (the object, the preprocessed file (preprocess) or cc1's assembly (cc1: these
        cc1 flags, cc1 only; its dumps next to it, <out>.i.<dump>), the compiler's log, its status)."""
        self.work.mkdir(parents=True, exist_ok=True)
        tag = f"{os.getpid()}_{tag}"  # several sessions may score the same unit
        c = self.work / f"{tag}.c"
        c.write_text(text)
        out = self.work / (f"{tag}.i" if preprocess else f"{tag}.s" if cc1 else f"{tag}.o")
        stop = ["-E"] if preprocess else ["-S", *(x for f in cc1 for x in ("--cc1", f))] if cc1 else []
        r = subprocess.run([str(ROOT / "tools/cc_psx.sh"), "-V", self.cc, "-G", str(self.g), *self.flags,
                            *(f"-I{d}" for d in includes), *(f"-D{d}" for d in defines),
                            *stop, str(c), "-o", str(out)],
                           capture_output=True, text=True, cwd=ROOT)
        return out, r.stdout + r.stderr, r.returncode

    def clean(self, tag: str):
        for f in self.work.glob(f"{os.getpid()}_{tag}.*"):
            f.unlink(missing_ok=True)

    def score(self, text: str, func: str, tag: str, keep=False, defines=(), includes=()) -> Score:
        """Score the unit's full text `text` for `func`."""
        obj, log, rc = self.compile(text, tag, defines, includes)
        try:
            if rc:
                return Score(error=compile_errors(log))
            try:
                pct = unit_diff.objdiff_percents(self.checker.expected, obj).get(func)
            except RuntimeError:
                pct = None
            res = self.checker.compare(obj)
            if func in res.asm:
                return Score(error="the function is still INCLUDE_ASM", links=res.links)
            reasons = res.functions.get(func, ["not in the C object"])
            ew, cw = res.words.get(func, ([], []))
            ndiff = sum(1 for a, b in zip(ew, cw) if a != b) + abs(len(ew) - len(cw))
            return Score(reasons=reasons, pct=pct, links=res.links, unit=res.unit, ndiff=ndiff,
                         mark=unit_diff.mark(res, func, pct), obj=obj if keep else None, res=res if keep else None)
        finally:
            if not keep:
                self.clean(tag)


def splice(unit_text: str, region: Region, replacement: str) -> str:
    return unit_text[:region.start] + replacement.strip("\n") + "\n" + unit_text[region.end:]


def put_text(unit_text: str, region: Region, c: str) -> str:
    """The unit's text with the C `c` in place of the function, without the declarations the unit already has."""
    return splice(unit_text, region, new_declarations(unit_text, region, c))


def keep(unit: Unit, func: str, region: Region, c: str, score: Score, wip: bool, note: str = None) -> str:
    """Write `c` in place of the function, checked: as C when it matches, as a WIP block when asked. Returns what
    was done; the file is left as it was when the check fails."""
    text = unit.text()
    if score.error is not None:
        return "not kept: it does not compile"
    if score.match:
        new, what = put_text(text, region, c), "kept as C"
    elif wip:
        folder = region.folder or unit.folder
        if not (ROOT / folder / f"{func}.s").exists():
            return f"not kept: no {folder}/{func}.s for the WIP's INCLUDE_ASM (a matched function stays C)"
        note = note or region.note or "; ".join(score.reasons)
        block = wip_block(new_declarations(text, region, c), wip_comment(score.percent(), note), folder, func)
        new, what = splice(text, region, block), f"kept as a WIP ({score.percent()})"
        _, log, rc = unit.compile(new, "keep_nm", defines=("NON_MATCHING",))
        unit.clean("keep_nm")
        if rc:
            return "not kept: the WIP block does not compile with -DNON_MATCHING: " + compile_errors(log)
    else:
        return "not kept: the unit is unchanged (--wip keeps it as a WIP)"
    if wip and not score.match:
        obj, log, rc = unit.compile(new, "keep")
        res = unit.checker.compare(obj) if not rc else None
        unit.clean("keep")
        if rc:
            return "not kept: the unit with the WIP block does not compile: " + compile_errors(log)
        if not res.links:
            return "not kept: the unit with the WIP block does not link to the original bytes: " + "; ".join(res.unit)
    unit.path.write_text(new)
    return what


# ---- variants and permutations --------------------------------------------------------------------------------------

def split_variants(text: str) -> list:
    return [v.strip("\n") + "\n" for v in re.split(r"(?m)^//---.*\n?", text) if v.strip()]


MARK = re.compile(r"^(?P<ind>[ \t]*)//@(?P<tag>P\w*|G\w+)(?:[ \t](?P<txt>.*))?$")
MARK_END = re.compile(r"^(?P<ind>[ \t]*)(?P<txt>\S.*?)[ \t]*//@(?P<tag>P\w*|G\w+)[ \t]*$")


class Template:
    """A perm template: lines marked //@P<set> (permuted within their set) and //@G<group> (one alternative per
    group). Candidate 0 is the template as written (each set in its order, each group's first alternative)."""

    def __init__(self, text: str):
        self.lines = text.split("\n")
        self.sets, self.groups = {}, {}
        for i, ln in enumerate(self.lines):
            m = MARK.match(ln) or MARK_END.match(ln)
            if not m:
                continue
            d = self.sets if m.group("tag").startswith("P") else self.groups
            d.setdefault(m.group("tag"), []).append((i, m.group("ind"), (m.group("txt") or "").rstrip()))
        self.radix = [math.factorial(len(v)) for v in self.sets.values()] + [len(v) for v in self.groups.values()]

    def count(self) -> int:
        return math.prod(self.radix)

    def candidate(self, index: int):
        """(the text, a description) of candidate `index`."""
        digits = []
        for r in reversed(self.radix):
            index, d = divmod(index, r)
            digits.append(d)
        digits.reverse()
        lines, desc = list(self.lines), []
        for (tag, items), d in zip(self.sets.items(), digits):
            order, pool = [], list(range(len(items)))
            for k in range(len(items), 0, -1):
                q, d = divmod(d, math.factorial(k - 1))
                order.append(pool.pop(q))
            for (i, ind, _), o in zip(items, order):
                lines[i] = ind + items[o][2]
            desc.append(f"{tag}: " + " ".join(str(o + 1) for o in order))
        for (tag, alts), d in zip(self.groups.items(), digits[len(self.sets):]):
            for n, (i, ind, txt) in enumerate(alts):
                lines[i] = (ind + txt) if n == d and txt else None
            desc.append(f"{tag}={d + 1}")
        return "\n".join(ln for ln in lines if ln is not None), ", ".join(desc)

    def indices(self, cap: int, seed: int = 0) -> list:
        total = self.count()
        if total <= cap:
            return list(range(total))
        rng, picked = random.Random(seed), {0}
        while len(picked) < cap:
            picked.add(rng.randrange(total))
        return [0] + sorted(picked - {0})


def score_many(unit: Unit, func: str, region: Region, texts: list, jobs: int, stop_on_match=False,
               defines=(), includes=(), progress=None):
    """Score each replacement text (a list of (id, text)) in parallel: [(id, Score)] in completion order."""
    base = unit.text()
    unit.checker  # set up once, before the threads
    results = []
    with ThreadPoolExecutor(max(1, jobs)) as ex:
        futs = {ex.submit(unit.score, put_text(base, region, t), func, f"c{n}", False, defines, includes): n
                for n, (_, t) in enumerate(texts)}
        for done, fut in enumerate(as_completed(futs), 1):
            n = futs[fut]
            results.append((texts[n][0], fut.result()))
            if progress and done % 50 == 0:
                progress(done, len(texts))
            if stop_on_match and results[-1][1].match:
                for f in futs:
                    f.cancel()
                break
    return results


def table(rows: list, limit: int, label: str = "#") -> str:
    """Ranked rows [(id, Score, description)]."""
    rows = sorted(rows, key=lambda r: r[1].key(), reverse=True)
    out = [f"{'rank':>4}  {label:>6}  result"]
    for rank, (ident, s, desc) in enumerate(rows[:limit], 1):
        out.append(f"{rank:>4}  {ident!s:>6}  {s}" + (f"   [{desc}]" if desc else ""))
    if len(rows) > limit:
        out.append(f"      ... {len(rows) - limit} more")
    return "\n".join(out)


# ---- the aligned diff -----------------------------------------------------------------------------------------------

BRANCH = re.compile(r"^(?:b(?!reak\b)\w*|j)\s")  # the branches and `j`: a target in the function, not a call
TARGET = re.compile(r"\b([0-9a-f]+) <[^>]*>")


def aligned(a: list, b: list, wa: list = None, wb: list = None) -> list:
    """The original's instructions `a` and the candidate's `b` ([(offset, text)], unit_diff.disasm_at) aligned by
    difflib: [(i, j, mark)], i or j None for an instruction only on one side. Instructions align on their linked
    words (`wa`, `wb`: unit_diff's, when there is one per instruction; else on their text), a branch on its text
    without its target; a pair of branches is the same only when their targets are aligned with each other too.
    Marks: ' ' the same, '~' the same once linked (another symbol or form), '|' differs, '<' only in the original,
    '>' only in the candidate."""
    def parse(lines, words):
        start = lines[0][0] if lines else 0
        keys, targets, texts = [], [], []
        for k, (_, t) in enumerate(lines):
            m = TARGET.search(t) if BRANCH.match(t) else None
            if m:
                targets.append((int(m.group(1), 16) - start) // 4)
                texts.append(TARGET.sub("T", t))
                keys.append(("branch", texts[-1].split("  ;")[0]))
            else:
                targets.append(None)
                texts.append(t)
                keys.append(("word", words[k]) if words is not None else ("text", t))
        return keys, targets, texts

    if wa is None or wb is None or len(wa) != len(a) or len(wb) != len(b):
        wa = wb = None
    ka, ta, xa = parse(a, wa)
    kb, tb, xb = parse(b, wb)
    pairs = []
    for op, i1, i2, j1, j2 in difflib.SequenceMatcher(None, ka, kb, autojunk=False).get_opcodes():
        if op == "equal":
            pairs += [(i, j, "=") for i, j in zip(range(i1, i2), range(j1, j2))]
            continue
        n = min(i2 - i1, j2 - j1) if op == "replace" else 0
        pairs += [(i1 + k, j1 + k, "|") for k in range(n)]
        pairs += [(i, None, "<") for i in range(i1 + n, i2)] + [(None, j, ">") for j in range(j1 + n, j2)]
    where = {i: j for i, j, _ in pairs if i is not None and j is not None}
    where[len(a)] = len(b)
    paired_b = set(where.values())

    def label(t, paired):  # a label before instructions only on one side is the label of the next paired one
        while t is not None and t not in paired and t < max(paired):
            t += 1
        return t
    out = []
    for i, j, m in pairs:
        if m == "=":
            if ta[i] is not None and where.get(label(ta[i], where)) != label(tb[j], paired_b):
                m = "|"
            else:
                m = " " if xa[i] == xb[j] else "~"
        out.append((i, j, m))
    return out


def aligned_lines(a: list, b: list, rows: list, context: int = 3) -> list:
    """The aligned rows side by side, runs of same instructions beyond `context` lines of a difference folded."""
    w = max([len(t) for _, t in a] + [10])
    lines = [f"{'original':{w}}   C   (| differs; < only in the original, > only in the C; ~ same once linked,"
             " other symbol or form)"]
    diff = [k for k, (_, _, m) in enumerate(rows) if m not in " ~"]
    show = set(range(len(rows))) if context < 0 else {
        k for d in diff for k in range(d - context, d + context + 1)}
    k = 0
    while k < len(rows):
        if k not in show:
            e = k
            while e < len(rows) and e not in show:
                e += 1
            lines.append(f"{'':{w}}    ... {e - k} the same")
            k = e
            continue
        i, j, m = rows[k]
        x = a[i][1] if i is not None else ""
        y = b[j][1] if j is not None else ""
        lines.append(f"{x:{w}} {' ' + m} {y}".rstrip())
        k += 1
    n = {m: sum(1 for *_, mm in rows if mm == m) for m in "|<>"}
    lines.append("aligned: " + (f"{n['|']} differ, {n['<']} only in the original, {n['>']} only in the C"
                                if diff else "no difference") + f" ({len(a)} and {len(b)} instructions)")
    return lines


# ---- cc1's register allocation (--dump) -----------------------------------------------------------------------------

DUMPS = {"l": "lreg", "g": "greg", "L": "loop", "c": "combine", "s": "cse", "t": "cse2", "f": "flow", "j": "jump",
         "J": "jump2", "S": "sched", "R": "sched2", "d": "dbr", "r": "rtl", "F": "addressof"}
REG_NAMES = ("zero at v0 v1 a0 a1 a2 a3 t0 t1 t2 t3 t4 t5 t6 t7 s0 s1 s2 s3 s4 s5 s6 s7 t8 t9 k0 k1 gp sp fp ra"
             .split())


def dump_letters(arg: str) -> str:
    """The cc1 -d letters of --dump's SECTIONS (letters or names, comma-separated); ValueError if unknown."""
    names = {v: k for k, v in DUMPS.items()}
    out = []
    for tok in filter(None, re.split(r"[,\s]+", arg)):
        if tok in names:
            out.append(names[tok])
        elif all(ch in DUMPS for ch in tok):
            out += list(tok)
        else:
            raise ValueError(tok)
    return "".join(dict.fromkeys(out))


def hard_reg(n: int) -> str:
    if n < 32:
        return REG_NAMES[n]
    if n < 64:
        return f"$f{n - 32}"
    return {64: "hi", 65: "lo", 66: "accum"}.get(n, f"$fcc{n - 67}" if n < 75 else str(n))


def function_dump(text: str, func: str):
    """The function's part of a cc1 dump, None when it has none."""
    m = re.search(rf"^;; Function {re.escape(func)}\n", text, re.M)
    if not m:
        return None
    e = text.find("\n;; Function ", m.end())
    return text[m.start():e if e >= 0 else len(text)].rstrip() + "\n"


def floor_log2(n: int) -> int:
    return n.bit_length() - 1 if n > 0 else -1


def allocation(lreg: str, greg: str) -> list:
    """Each pseudo of a function's -dl/-dg dumps (flow's `Register N used R times across L insns`, local-alloc's
    `;; Register N in H.`, global-alloc's order, preferences and dispositions), in global-alloc's order, then the
    others by number: dicts with reg, refs, live, block, size, notes, user (a variable's pseudo), prio, rank (in
    global-alloc's order), local (local-alloc's hard register), hard (the hard register at the end, None: none)."""
    pseudos = {}
    for m in re.finditer(r"^Register (\d+) used (\d+) times? across (-?\d+) insns?([^\n]*)", lreg, re.M):
        n, refs, live, rest = int(m.group(1)), int(m.group(2)), int(m.group(3)), m.group(4)
        block = re.search(r"^ in block (\d+)", rest)
        size = re.search(r"; (\d+) bytes", rest)
        notes = []
        calls = re.search(r"; crosses (\d+) calls?", rest)
        if calls:
            notes.append(f"crosses {calls.group(1)} call" + ("s" if calls.group(1) != "1" else ""))
        pref = re.search(r"; pref (\w+)", rest)
        if pref and pref.group(1) != "GR_REGS":
            notes.append("class " + pref.group(1))
        if "; pointer" in rest:
            notes.append("pointer")
        size = -(-int(size.group(1)) // 4) if size else 1  # in words, as global-alloc counts it
        prio = floor_log2(refs) * refs / live * size if live > 0 else None
        pseudos[n] = dict(reg=n, refs=refs, live=live, block=int(block.group(1)) if block else None, size=size,
                          notes=notes, user=bool(re.search(rf"\(reg/v[^ ]* {n}\)", lreg)), prio=prio, rank=None,
                          local=None, hard=None, prefs=[])
    for m in re.finditer(r"^;; Register (\d+) in (\d+)\.", lreg, re.M):
        if int(m.group(1)) in pseudos:
            pseudos[int(m.group(1))]["local"] = int(m.group(2))
    order = re.search(r"^;; \d+ regs to allocate:([^\n]*)", greg, re.M)
    if order:
        for rank, tok in enumerate(re.findall(r"\d+(?:\+\d+)*", re.sub(r" \(\d+\)", "", order.group(1))), 1):
            for k, r in enumerate(tok.split("+")):
                if int(r) in pseudos:
                    pseudos[int(r)]["rank"] = rank
                    if k:
                        pseudos[int(r)]["notes"].append("tied to " + tok.split("+")[0])
    for m in re.finditer(r"^;; (\d+) preferences:([^\n]*)", greg, re.M):
        if int(m.group(1)) in pseudos:
            pseudos[int(m.group(1))]["prefs"] = [hard_reg(int(x)) for x in m.group(2).split()]
    disp = re.search(r"^;; Register dispositions:\n(.*?)(?:\n\s*\n|\n;;|\Z)", greg, re.M | re.S)
    if disp:
        for m in re.finditer(r"(\d+) in (\d+)", disp.group(1)):
            if int(m.group(1)) in pseudos:
                pseudos[int(m.group(1))]["hard"] = int(m.group(2))
    return sorted(pseudos.values(), key=lambda p: (p["rank"] is None, p["rank"] or 0, p["reg"]))


SDB_CLASS = {4: "reg", 17: "reg", 1: "stack", 9: "arg"}


def variables(asm: str, func: str) -> list:
    """The function's variables and where they live, from cc1 -g's .def lines: [(name, where)]."""
    m = re.search(rf"^\s*\.def\s+{re.escape(func)};.*$", asm, re.M)
    if not m:
        return []
    e = re.search(rf"^\s*\.end\s+{re.escape(func)}\s*$", asm[m.end():], re.M)
    body = asm[m.end():m.end() + e.start() if e else len(asm)]
    defs = [(d.group(1), int(d.group(2)), int(d.group(3))) for d in re.finditer(
        r"\.def\s+([A-Za-z_]\w*);\s*\.val\s+(-?\d+);\s*\.scl\s+(\d+);", body)]
    out = []
    for name, val, scl in defs:
        kind = SDB_CLASS.get(scl)
        if kind is None or kind == "arg" and any(n == name and c in (4, 17) for n, _, c in defs):
            continue
        out.append((name, hard_reg(val) if kind == "reg" else "stack"))
    return out


def dump(unit: Unit, text: str, func: str, letters: str = "", defines=()) -> list:
    """cc1's register allocation of `func` in the unit's text `text`, and the dumps' text of `letters`: lines."""
    out, log, rc = unit.compile(text, "dump", defines, cc1=["-d" + "".join(dict.fromkeys("lg" + letters))])
    try:
        if rc:
            return ["dump: compile error: " + compile_errors(log)]
        parts = {}
        for ch in dict.fromkeys("lg" + letters):
            f = Path(f"{out}.i.{DUMPS[ch]}")
            parts[ch] = function_dump(f.read_text(errors="replace"), func) if f.exists() else None
        if parts["l"] is None or parts["g"] is None:
            return [f"dump: no {func} in cc1's -dl/-dg dumps"]
        rows = allocation(parts["l"], parts["g"])
        local = [p for p in rows if not p["rank"] and p["local"] is not None]
        lines = [f"cc1 -dl -dg, gcc {unit.cc} -G{unit.g}: {func}, {len(rows)} pseudos, in global-alloc's order"
                 " (priority = floor_log2(refs) x refs / live x size), then local-alloc's",
                 f"  {'pseudo':>6}  {'refs':>4}  {'live':>4}  {'prio':>6}  {'alloc':<9} {'reg':<5} notes"]
        if not rows:
            lines[1:] = ["  no pseudo register"]
        for p in rows:
            if p in local:
                continue
            alloc = f"global {p['rank']}" if p["rank"] else "none"
            hard = "-" if p["hard"] is None else hard_reg(p["hard"])
            notes = [*(["variable"] if p["user"] else []),
                     *([f"block {p['block']}"] if p["block"] is not None and p["rank"] else []),
                     *p["notes"], *(["prefers " + " ".join(p["prefs"])] if p["prefs"] else [])]
            prio = "-" if p["prio"] is None else f"{p['prio']:.2f}"
            lines.append(f"  {p['reg']:>6}  {p['refs']:>4}  {p['live']:>4}  {prio:>6}  {alloc:<9} {hard:<5} "
                         + ", ".join(notes))
        blocks = {}
        for p in local:
            blocks.setdefault(p["block"], []).append(
                f"{p['reg']} {'-' if p['hard'] is None else hard_reg(p['hard'])} {p['refs']}/{p['live']}"
                + "".join(f" ({n})" for n in p["notes"] if not n.startswith("pointer")))
        if blocks:
            lines.append("  local-alloc, per block: pseudo reg refs/live")
            for b, ps in sorted(blocks.items()):
                lines += textwrap.wrap(", ".join(ps), 116, initial_indent=f"  b{b}: ", subsequent_indent=" " * 6)
        gout, _, grc = unit.compile(text, "dump_g", defines, cc1=["-g"])
        if not grc:
            v = variables(gout.read_text(errors="replace"), func)
            if v:
                lines.append("  variables (-g): " + ", ".join(f"{n} {w}" for n, w in v))
        for ch in letters:
            body = parts.get(ch)
            lines.append(f"---- cc1 -d{ch} ({DUMPS[ch]}): " + ("" if body else f"no {func}"))
            if body:
                lines += body.rstrip("\n").split("\n")
        return [ln.rstrip() for ln in lines]
    finally:
        unit.clean("dump")
        unit.clean("dump_g")


# ---- the command line -----------------------------------------------------------------------------------------------

def locate(func: str, target: str = None, unit: str = None):
    """(target, unit) whose C has the function (its INCLUDE_ASM or its definition)."""
    targets = [target] if target else [t.name for t in configure.TARGETS]
    for t in targets:
        base = ROOT / "src" / t
        paths = [base / f"{unit}.c"] if unit else sorted(base.rglob("*.c"))
        for p in paths:
            if p.exists() and func in (text := p.read_text()) and find(text, func):
                return t, p.relative_to(base).with_suffix("").as_posix()
    sys.exit(f"{func}: not found in src/{target or '*'}/" + (f"{unit}.c" if unit else ""))


def show_diff(unit: Unit, func: str, s: Score, context: int = 3):
    if s.obj is not None and s.res is not None and func in s.res.words:
        a, b = unit_diff.disasm_at(unit.checker.expected, func), unit_diff.disasm_at(s.obj, func)
        print()
        print("\n".join(aligned_lines(a, b, aligned(a, b, *s.res.words[func]), context)))


def show_dump(unit: Unit, text: str, func: str, letters, defines=()):
    if letters is not None:
        print()
        print("\n".join(dump(unit, text, func, letters, defines)))


def read_input(path: str) -> str:
    return sys.stdin.read() if path == "-" else Path(path).read_text()


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("cmd", choices=["get", "put", "try", "perm"])
    ap.add_argument("func")
    ap.add_argument("file", nargs="?")
    ap.add_argument("-t", "--target")
    ap.add_argument("-u", "--unit")
    ap.add_argument("-j", "--jobs", type=int, default=int(os.environ.get("RMPG2_JOBS") or 4))
    ap.add_argument("-k", "--keep", nargs="?", const=0, type=int, metavar="N",
                    help="try: keep variant N (1-based); perm: keep the best")
    ap.add_argument("--wip", action="store_true", help="keep a candidate that does not match as a WIP block")
    ap.add_argument("--note", help="the WIP comment's note (what differs)")
    ap.add_argument("-s", "--show", action="store_true", help="the aligned side-by-side diff")
    ap.add_argument("-C", "--context", type=int, default=3, help="-s: lines of context (-1: all)")
    ap.add_argument("--dump", nargs="?", const="", metavar="SECTIONS",
                    help="cc1's register allocation (-dl -dg), and these dumps' text of the function")
    ap.add_argument("-n", type=int, default=15, help="rows of the ranked table")
    ap.add_argument("--max", type=int, default=5040, help="perm: at most this many candidates (sampled beyond)")
    ap.add_argument("--seed", type=int, default=0)
    ap.add_argument("-V")
    ap.add_argument("-G", type=int)
    ap.add_argument("-D", action="append", default=[], metavar="DEF")
    a = ap.parse_args()
    if a.dump is not None:
        try:
            a.dump = dump_letters(a.dump)
        except ValueError as e:
            if a.file is not None or a.cmd == "get":
                ap.error(f"--dump: {e}: not a dump (letters {''.join(DUMPS)}, or names: {', '.join(DUMPS.values())})")
            a.file, a.dump = a.dump, ""  # `--dump file.c`: the file, not the sections
    if a.cmd != "get" and not a.file:
        ap.error(f"{a.cmd} needs a file")

    target, name = locate(a.func, a.target, a.unit)
    unit = Unit(target, name, cc=a.V, g=a.G)
    text = unit.text()
    region = find(text, a.func)
    defines = a.D

    if a.cmd == "get":
        if region.kind == "asm":
            sys.exit(f"{a.func}: INCLUDE_ASM in src/{target}/{name}.c")
        if a.dump is not None:
            print("\n".join(dump(unit, splice(text, region, region.c), a.func, a.dump, defines)))
            return
        print(region.c, end="")
        if region.kind == "wip":
            print(f"// WIP in src/{target}/{name}.c" + (f": {region.note}" if region.note else ""), file=sys.stderr)
        return

    print(f"{a.func}: src/{target}/{name}.c ({region.kind}), gcc {unit.cc} -G{unit.g}", flush=True)
    if a.cmd == "put":
        c = read_input(a.file)
        s = unit.score(put_text(text, region, c), a.func, "put", keep=a.show, defines=defines)
        print(f"  {s}")
        if a.show:
            show_diff(unit, a.func, s, a.context)
        show_dump(unit, put_text(text, region, c), a.func, a.dump, defines)
        print("  " + keep(unit, a.func, region, c, s, a.wip, a.note) if not defines else "  not kept (-D given)")
        unit.clean("put")
        sys.exit(0 if s.match else 1)

    if a.cmd == "try":
        variants = split_variants(read_input(a.file))
        rows = score_many(unit, a.func, region, list(enumerate(variants, 1)), a.jobs, defines=defines)
        print(table([(n, s, "") for n, s in rows], a.n, "variant"))
        best = max(rows, key=lambda r: r[1].key())
        pick = a.keep if a.keep else best[0]
        if a.show or a.dump is not None:
            if not 1 <= pick <= len(variants):
                sys.exit(f"-k {pick}: there are {len(variants)} variants")
            print(f"\nvariant {pick}:", end="" if a.show else "\n")
        if a.show:
            s = unit.score(put_text(text, region, variants[pick - 1]), a.func, "show", keep=True, defines=defines)
            show_diff(unit, a.func, s, a.context)
            unit.clean("show")
        show_dump(unit, put_text(text, region, variants[pick - 1]), a.func, a.dump, defines)
        if a.keep is not None and not defines:
            if not 1 <= pick <= len(variants):
                sys.exit(f"-k {pick}: there are {len(variants)} variants")
            s = dict(rows)[pick]
            print(f"variant {pick}: " + keep(unit, a.func, region, variants[pick - 1], s, a.wip, a.note))
        sys.exit(0 if best[1].match else 1)

    tpl = Template(read_input(a.file))
    total = tpl.count()
    if total <= 1:
        sys.exit("perm: no //@P lines or //@G alternatives in the template")
    idx = tpl.indices(a.max, a.seed)
    seen, cands = set(), []
    for i in idx:
        t, desc = tpl.candidate(i)
        if t not in seen:
            seen.add(t)
            cands.append((i, t, desc))
    print(f"  {total} candidates" + (f", {len(idx)} sampled (--max)" if len(idx) < total else "")
          + (f", {len(cands)} distinct" if len(cands) < len(idx) else "") + f", -j {a.jobs}", flush=True)
    byid = {i: (t, d) for i, t, d in cands}
    rows = score_many(unit, a.func, region, [(i, t) for i, t, _ in cands], a.jobs, stop_on_match=True,
                      defines=defines,
                      progress=lambda d, n: print(f"  ... {d}/{n}", file=sys.stderr, flush=True))
    print(table([(i, s, byid[i][1]) for i, s in rows], a.n, "cand"))
    best_id, best = max(rows, key=lambda r: r[1].key())
    out = unit.work / f"{a.func}.best.c"
    out.write_text(byid[best_id][0])
    print(f"best: candidate {best_id} [{byid[best_id][1]}], {'a match' if best.match else best.percent()}:"
          f" {out.relative_to(ROOT)}")
    if best.match:
        print(byid[best_id][0], end="")
    if a.show:
        s = unit.score(put_text(text, region, byid[best_id][0]), a.func, "show", keep=True, defines=defines)
        show_diff(unit, a.func, s, a.context)
        unit.clean("show")
    show_dump(unit, put_text(text, region, byid[best_id][0]), a.func, a.dump, defines)
    if a.keep is not None and not defines:
        print(keep(unit, a.func, region, byid[best_id][0], best, a.wip, a.note))
    sys.exit(0 if best.match else 1)


if __name__ == "__main__":
    main()
