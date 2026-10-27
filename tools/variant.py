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
  -s                    the side-by-side instruction diff of the candidate (put), of the kept or the best (try, perm)
  -t TARGET, -u UNIT    where the function is (default: found under src/); -j N parallel compiles (RMPG2_JOBS, 4)
  -V VER, -G N, -D DEF  as tools/unit_diff.py (nothing is kept with -D)

A replacement is the function's definition, ANSI or K&R, optionally with declarations before it (they move with
it). Markers (perm), on a line of their own or at the end of a statement's line:
      //@P a->x = 0;          a line of the permuted set P (`//@P2 ...` another set, permuted independently)
      a->y = 0; //@P          the same, the line compilable as it is
      //@G1 n = 3 - x;        alternatives of group G1: one is kept, the others dropped
      //@G1                   an empty alternative: none of the group's lines
"""
import argparse
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
                return Region(start, m.end() + em.end(), "wip", body.strip("\n") + "\n", note, folder)
        return Region(m.start(), m.end(), "asm", None, None, folder)
    for m in re.finditer(rf"^[A-Za-z_][^\n;{{}}=]*?\b{f}\s*\(", text, re.M):
        end = definition_end(text, m.end() - 1)
        if end:
            return Region(m.start(), end, "c", text[m.start():end])
    return None


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

    def compile(self, text: str, tag: str, defines=(), includes=(), preprocess=False):
        """Compile `text` as this unit: (the object or the preprocessed file, the compiler's log, its status)."""
        self.work.mkdir(parents=True, exist_ok=True)
        tag = f"{os.getpid()}_{tag}"  # several sessions may score the same unit
        c = self.work / f"{tag}.c"
        c.write_text(text)
        out = self.work / (f"{tag}.i" if preprocess else f"{tag}.o")
        r = subprocess.run([str(ROOT / "tools/cc_psx.sh"), "-V", self.cc, "-G", str(self.g), *self.flags,
                            *(f"-I{d}" for d in includes), *(f"-D{d}" for d in defines),
                            *(["-E"] if preprocess else []), str(c), "-o", str(out)],
                           capture_output=True, text=True, cwd=ROOT)
        return out, r.stdout + r.stderr, r.returncode

    def clean(self, tag: str):
        for suffix in (".c", ".o", ".o.i", ".o.s", ".o.m.s", ".i"):
            (self.work / f"{os.getpid()}_{tag}{suffix}").unlink(missing_ok=True)

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


def put_text(unit_text: str, region: Region, replacement: str) -> str:
    return unit_text[:region.start] + replacement.strip("\n") + "\n" + unit_text[region.end:]


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
        block = wip_block(c, wip_comment(score.percent(), note), folder, func)
        new, what = put_text(text, region, block), f"kept as a WIP ({score.percent()})"
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


def show_diff(unit: Unit, func: str, s: Score):
    if s.obj is not None and s.res is not None and func in s.res.words:
        print()
        print("\n".join(unit_diff.side_by_side(unit.checker.expected, s.obj, s.res, func)))


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
    ap.add_argument("-s", "--show", action="store_true", help="side-by-side diff")
    ap.add_argument("-n", type=int, default=15, help="rows of the ranked table")
    ap.add_argument("--max", type=int, default=5040, help="perm: at most this many candidates (sampled beyond)")
    ap.add_argument("--seed", type=int, default=0)
    ap.add_argument("-V")
    ap.add_argument("-G", type=int)
    ap.add_argument("-D", action="append", default=[], metavar="DEF")
    a = ap.parse_args()
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
            show_diff(unit, a.func, s)
        print("  " + keep(unit, a.func, region, c, s, a.wip, a.note) if not defines else "  not kept (-D given)")
        unit.clean("put")
        sys.exit(0 if s.match else 1)

    if a.cmd == "try":
        variants = split_variants(read_input(a.file))
        rows = score_many(unit, a.func, region, list(enumerate(variants, 1)), a.jobs, defines=defines)
        print(table([(n, s, "") for n, s in rows], a.n, "variant"))
        best = max(rows, key=lambda r: r[1].key())
        pick = a.keep if a.keep else best[0]
        if a.show:
            s = unit.score(put_text(text, region, variants[pick - 1]), a.func, "show", keep=True, defines=defines)
            print(f"\nvariant {pick}:", end="")
            show_diff(unit, a.func, s)
            unit.clean("show")
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
        show_diff(unit, a.func, s)
        unit.clean("show")
    if a.keep is not None and not defines:
        print(keep(unit, a.func, region, byid[best_id][0], best, a.wip, a.note))
    sys.exit(0 if best.match else 1)


if __name__ == "__main__":
    main()
