# Matching functions

The practical guide to turning a function's assembly into C that rebuilds byte-identical. The compiler evidence is
in [`TOOLCHAIN.md`](TOOLCHAIN.md): GCC 2.8.1 `-O2 -G0`, the same compiler the C patterns at the end were found on,
in another PS1 project of the same era ([`THIRD_PARTY.md`](THIRD_PARTY.md)), so they apply here as they are.

## Setup

```sh
scripts/worktree_init.sh          # in a fresh worktree: links tools/, iso/, extracted/ from the main checkout (~1 s)
export RMPG2_JOBS=1               # when several people or agents share a machine: one job each
scripts/build.sh                  # splat + ninja; must end "build passed" (also makes build/expected/ for unit_diff)
```

- `scripts/build.sh --check` splits and builds from scratch. Run it after config or symbol-file changes, and once
  before you hand in work. For C-only changes the incremental `scripts/build.sh` is enough: ninja still checks every
  output's SHA-1.
- Trust only the build script's exit code; never pipe it into `head` before `&&`.
- Scratch files go in your own scratch directory, never in the repository.

## Tools

| Tool | Use |
|---|---|
| splat (`configure.py`) | Splits each target from `config/<target>.yaml` into `asm/<t>/` and `src/<t>/` stubs; `configure.py` also writes `build.ninja` and `objdiff.json` |
| `tools/cc_psx.sh` | The one compile path: cpp → cc1 (`-O2`) → maspsx → GNU as. ninja, the permuter and the scripts all use it. `-V`, `-G`, `-D`, `--data-in-c` |
| m2c (`tools/ext/m2c`) | First draft: `m2c.py --target mipsel-gcc-c --context <ctx.h> asm/<t>/nonmatchings/<unit>/<func>.s` |
| `tools/compiler_id.py` | m2c drafts of a whole target, compiled with every GCC, scored; the exact ones are free matches |
| `tools/unit_diff.py <unit> [func] [-t <target>] [-D NON_MATCHING]` | Scores one C unit against the original per function and data section, no ninja, parallel-safe; with a function, a side-by-side instruction diff |
| objdiff (`tools/bin/objdiff-cli`) | Per-function diff and the progress report (`objdiff.json`) |
| asm-differ (`tools/ext/asm-differ/diff.py -mw <func>`) | Live terminal diff |
| decomp-permuter (`tools/ext/decomp-permuter`) | Random source mutations scored against the target; a hint, never the answer |
| `tools/split_case_sizes.py asm/<t>/X.s` | `size:` lines that merge switch-case pieces spimdisasm split off as `jlabel` functions |
| `tools/psyq_match.py` | Psy-Q library objects by signature (`--symbols` writes their names); `--functions` names the functions of the config's `psyq/` units one by one |
| cc1 dump flags | `-dL` (loop.c hoisting decisions), `-dl`/`-dg` (local/global allocation priorities) |

GCC 2.8.1's sources, for reading why the compiler chose something:
`https://raw.githubusercontent.com/gcc-mirror/gcc/releases/gcc-2.8.1/gcc/<file>.c` (`sched.c`, `loop.c`, `local-alloc.c`,
`global.c`, `jump.c`, `reorg.c`, `cse.c`).

## How targets are configured

- One `config/<target>.yaml` per link unit; the executable is `main`. Each has a `Target` in `configure.py` and a
  `config/<NAME>.sha1`.
- `-G`: `configure.py` `DEFAULT_G` and `G_OVERRIDES` per file. `DATA_IN_C` lists units whose data is defined in C.
- Names and sizes: `config/symbol_addrs.txt` (the executable) and `config/<overlay>.symbols.txt` (`name = 0x80012345;
  // type:func`, `size:0x34` for structs).
- After a symbol-file change splat can keep stale `asm/<t>/nonmatchings/*.s`: delete `asm/<t>` or run `build.sh --check`.
- `permuter_settings.toml` compiles at `-G 0`; set the file's `-G` there when permuting a function of another file.

## The loop per function

1. **Draft** with m2c (or take the `compiler_id.py` draft) and replace the `INCLUDE_ASM` in `src/<t>/<unit>.c`.
   m2c misreads arguments of calls through function pointers (check `a2`/`a3` and stack stores in the asm) and its
   store order is not source order.
2. **Score** with `tools/unit_diff.py <unit> <func>`. A near-100% "label-only" difference can hide a real one (a
   missing `default:`), and unit_diff does not check function order within the file, which the link needs: only the
   build proves a match.
3. **Iterate on natural C**: types, struct fields, statement order, a variable per job (the patterns below). Look for
   an already matched sibling first.
4. **Stop** after about 30-45 minutes on one function: put the C under `#ifdef NON_MATCHING` with the `INCLUDE_ASM` in
   the `#else`, plus a comment with the score and the remaining difference. Every WIP must compile with
   `-DNON_MATCHING` (`unit_diff.py <unit> -D NON_MATCHING`).
5. **Build and commit** every ~10 matches: `scripts/build.sh` must say "build passed" (`--check` after config or symbol
   changes).

## Conventions

- **Names:** game functions and globals are `<module>_<verb>_<noun>` in snake_case, the prefix being the defining C
  file (`src/main/cdload.c` → `cdload_read_file`). Types PascalCase (`<Module><Noun>`), constants
  `MODULE_UPPER_SNAKE`, unknown fields `unk_<offset>`, alignment padding `pad_<offset>`. Only what is understood is
  named; otherwise splat's `func_<addr>`/`D_<addr>`. An original name found in the binary wins; Psy-Q names stay
  Sony's. Rename everywhere at once (`grep -rn` over `src/ include/ config/`).
- **Match status:** a function is matching when it compiles from C and the whole build is byte-identical; otherwise
  it stays `INCLUDE_ASM`, with any WIP C under `#ifdef NON_MATCHING`. Matching C must be natural: no dummy
  temporaries, bare `do {} while (0)` or other permuter-only shapes.
- **Module state:** function-pointer tables and module state are sized structs. A label-only mismatch inside a struct
  is fixed with a `size:` entry, never with scalar externs per label.
- Types used by one file stay in it; shared ones go in `include/<module>.h`. Unknown types `Unk<addr>`.
- One declaration per symbol, in a header. When callers see a wider type than the definition (a `u8` getter called as
  `s32` through a module table), the table entry gets the callers' type with a comment.
- Never decompile Psy-Q code (`psyq/` units). The interface the game calls is declared in `include/psyq/<lib>.h`,
  written from the game's own code; no SDK header.
- Shared files (`include/common.h`, `configure.py`): add what you need, append rather than reorder, and list every
  change when you hand in.

## Splitting a target into files

Each target is split into the C files the original had, and every boundary carries its evidence in the YAML:
- **Jump-table parity:** objects are packed at 4, tables 8-aligned within their object, so a table whose
  `(address - base) mod 8` differs from the previous one's starts a new object. A zero pad word after an odd-length
  table ties the next table to the same object. Equal parity proves nothing (a coin toss per boundary).
- **Link order:** psylink places every object's `.rodata` (before all `.text`) and `.data` in link order, which is
  the order of the objects' `.text`. A jump table or a string literal belongs to the object of the function that
  uses it, so the sequence of their users along `.rodata` is the file order; a `.data` piece belongs to the object
  at its position in `.data`, whoever uses it (globals are used from anywhere, so `.data` order places a file's
  definitions, not its users). Data-only objects (tables, strings, generated files) sit between code files in both
  sections: a run of `.data` with no code users between two files' pieces proves a boundary between those files.
- **Positions:** create/update pairs, static helpers placed just before their only caller, define-before-use, each
  module's function table, `$gp` users (ASPSX uses `$gp` only for symbols defined earlier in the same file, so a
  `$gp` user and its variable share a file), helpers duplicated byte for byte (a copy of a known file proves both
  its boundaries). Function alignment is not evidence (every function is 4-aligned).
- `.bss` is no evidence here: uninitialised globals are COMMON symbols, placed by the linker in an order of its own.

Then replace the `asm` subsegments in `config/<target>.yaml` with per-file `.rodata`, `c` and `data` subsegments, a
comment with each boundary's evidence (weak ones marked weak), run `configure.py`, check the build stays
byte-identical and commit the split before decompiling. No evidence: no split. The executable's files and what is
known of them are in [`DISC_LAYOUT.md`](DISC_LAYOUT.md) "The files".

## C patterns

Each pattern below matched at least one GCC 2.8.1 function. Try them before searching blindly.

### Types and calls
- A missing argument load means the callee takes no arguments; a register the original never sets is not an argument;
  a parameter used without sign extension is an `int`.
- An `lh` where `lhu` was expected means a copy through an `s32` local; `x * -1` loads with `lh`.
- Unused locals and structs show in the frame size; a struct passed by value shows as `a0`/`a1` home-slot stores.
- A function that leaves its object in `v0` returns it (`return obj;` changes no code); constructors whose result
  callers use return their object.
- Method slots keep word-sized parameters: narrowing a slot's parameter type changes the callers' bytes.

### Structs, globals and aliasing
- GCC 2.8 assumes a struct field and a scalar global never alias. A global reloaded after a struct-field store is a
  struct member: make it a one-member struct (also for a function-pointer global called right after such stores).
- Code that reaches `X + 0x68` and `X + 0x7C` with a hoisted `%hi` only matches as separate symbols.
- cse forgets every field of a struct pointer after any store through it: the original's field reloads show where its
  stores sit.
- A store through a computed pointer conflicts with any symbol-based load unless the store is into a struct or array
  and the load isn't. A local base (`s32 *sheet = D_...`) escapes the symbol-vs-pointer conflict.
- GCC builds `la sym` + offset for struct globals; combine folds it unless the base has several uses, the use is in
  another block, a call intervenes, or the MEM is volatile.
- A constant index folded into a load offset (`lbu 2(v0)`) reveals a real middle array dimension (`[4][2][2]`).
- Split an array where every use has a constant index; merge fields where a use indexes past an array's end.
- Pointer-linked record sets are one array with `&arr[i]` pointers. Struct layouts include tail padding.

### Operand order and arithmetic
- `x->arr[k]` emits `addu x,k`; `*(x->arr + k)` emits `addu k,x`. An array inside a struct puts the base after the
  index offset.
- When the original adds the offset to the struct base (`addu obj,k`) and every index form gives `addu k,obj`, a
  `static inline` accessor gives the original's order (its parameters are fresh pseudos).
- Indexing a table directly (`T[i].a … T[i].b`) loads the base first, a pointer local doesn't; use `Entry *e =
  &array[i]` when the original computes `i * size` before the base.
- fold reassociates `y + (t + c)` into `(y + c) + t`: write `y + c + t` to get `t + c` first. `v + c + i * k` keeps
  the original's order; `a - -b` keeps `a` first.
- The left operand of a comparison loads first, so `a > b` and `b < a` differ.
- GCC computes an assignment's left-hand array address before the right-hand side; only an inlined call on the right
  reverses it.
- `n = 3; n -= x;` and `n = 3 - x` differ. `1 - (x != 0)` folds to `x == 0`: if the original subtracts, the `!= 0`
  value was its own variable.
- `s16 / const` becomes a 16-bit divide plus sign extension; without the `sll/sra 16` the dividend went through an
  int.
- `if (p == NULL) return 1; return 0;` becomes `sltiu` unless the `return 0` is shared.
- Chained `a = b = v` stores `b` first.
- `addiu -a; sltiu n` then an `== k` test is `if (x >= a && x < a + n) … else if (x == k)`, not a switch.
- A value loaded before a branch on another variable can be a `?:` inside the comparison (jump threading).
- cse doesn't merge `(x + 1) * 8 - 1` with `x * 8`.

### Register allocation
- Global allocation priority is `floor_log2(refs) × refs / live_length` (`-dl`/`-dg` print it); references inside a
  loop count twice. Code repeated per case or branch and merged later by cross-jumping still counts.
- Give each job its own variable: one per loop, one per switch case (block-local), one per branch when branches swap
  fields, fresh block-locals for intermediates. Yet the original also reuses counters and flags across loops: try a
  rename search over both directions.
- A value used both before and after a call wants its own variable assigned once.
- local-alloc ties a block-local result to its dying first operand (and never to a pseudo set more than once in its
  block); global-alloc then prefers that operand's variable for the result.
- A value used in two blocks becomes a global pseudo, which changes local-alloc's `v0`/`v1` choices.
- A local initialised at its declaration has a longer live range. Statement order within store runs changes live
  lengths; declaration order rarely matters.
- cse makes the longer-lived copy canonical (after `tim = p`, later uses of `p` become `tim`). A local holding a
  `lui/ori` constant stays in one register. Constant-init order decides which register cse copies from.
- reload_cse has no cost check: `move vX,sY` at a constant store means the constant was stored before the variable
  was set.
- When the original copies a value just stored into a field, write the read through the field.
- When the original advances one register through a packet (`POLY_FT4` → `SPRT` → `DR_TPAGE`), keep one running
  pointer (`poly = (POLY_FT4 *)(sprt + 1)`), and step it in place.
- Repeated `lui`/`li` before each use inside a loop is reload rematerialising a hoisted constant that got no register.

### Scheduling and store order
- Independent stores keep source order through the scheduler; swap chains are ordered by when their fields are read.
- sched1 gives top priority to an insn setting a live, once-assigned pseudo, so a load into a fresh block-local sits
  right before its use; a variable assigned more than once keeps its statement position. A value read before a store
  it could alias is a block-local initialiser.
- Scheduling ties go to the later insn in RTL order: an unrelated statement between a copy and a test can decide.
- A store fed by a load sinks below independent constant stores (load latency).
- A statement placed after a call moves delay-slot fills; code after a branch can decide that branch's delay slot.
- Pass order: sched1 → … → sched2 → jump2 (cross-jumping) → reorg. Analyse tail merges in sched2's order.

### Switches and cross-jumping
- A jump table needs at least 5 case labels (5 sparse cases still gave a compare tree, 6 a table). `slti`+`bltz` range
  tests come from a switch with adjacent cases. Check the jump table before believing a fallthrough.
- Case bodies are emitted in source order: order cases as the original places them, but try numeric order first, since
  a case out of order can switch cross-jumping on or off.
- Hidden empty cases decide codegen: `case 0: break;` when the table starts at 0; `case 0: default:` in object
  `switch (state)`es; a `slti` in a `u8` switch tree means an explicit `case 0:` sharing the default.
- An out-of-line stub jumping into a shared tail means the source wrote the tail in each branch: write the final call,
  `return` or clear per branch when the original has them per branch. A variable per case stops tail merging.
- Cross-jumping is order dependent: a tail first merges into the code before its target label. Put `case 0: default:`
  first to keep per-case tails separate. Branch sense decides which copies merge.
- GCC emits a self tail call as `j` only for `return f(...)` in an int function.
- spimdisasm may start a "function" at a jump-table target: merge it back with `split_case_sizes.py`'s `size:` line.

### Loops
- loop.c hoists an invariant when threshold × savings × lifetime ≥ the loop's insn count (threshold 1 + the number of
  non-fixed registers, 29 here, with calls; −3 per value already moved; a `%hi/%lo` pair has life 2). `-dL` prints each
  decision. If the original reloads inside the loop, its loop was bigger: one more use, a per-branch tail or a type
  change can flip it, never `-f` flags.
- GCC 2.8.1 reverses count-up loops into count-down pointer loops: write them count-up.
- Screen positions are `i * step + base` (loop.c reduces them), not `x += step` counters.
- Table scans: an index loop (`T[i].x`) when the asm sets the walking pointer in the preheader and hoists the sentinel
  separately; `for (i = 0; D[i].x != -1; i++) { t = &D[i]; … }` avoids an extra induction variable. Some really are
  pointer walks.
- `found[count++] = i` and `*p++ = i` differ; a pointer step in the `for` increment (`i++, p++`) gives
  increment-before-load.
- A loop entered at its test comes from code after the loop duplicated in each branch. A "first non-zero" search:
  `i = 0; while (a[i] == 0) { if (++i >= N) break; }`.
- A global pointer read as an array element is reloaded in loops, a scalar global hoisted.
- Every loop that crosses a call needs its own variable. A giv kept in a user variable pays a copy cost, so extra givs
  in the original were compiler temporaries.
- GCC shares stack slots only between variables of nested blocks: a frame bigger than the original's means the original
  nested its blocks (often macro blocks).

### Small data and data in C
- ASPSX uses `$gp` only for symbols defined earlier in the same file, so a `$gp` user and its variable share a file,
  and that file defines it. Taking a `$gp` variable's address (`addiu rX, $gp, %gp_rel(x)`) needs ASPSX 2.80.
- In a `-G8` file every extern of 8 bytes or less is possible small data. Where the original uses a `%hi/%lo` pair,
  declare the symbol with its real larger type or an incomplete type.
- `.bss` order is the order of first declaration (an earlier `extern`, even in a header, fixes it). Explicit zero
  initialisers stay in `.data`.
- Strings of a table's initialisers are emitted where the table is defined, last element first, and GCC shares an
  identical literal within one file only.
- A function's `.rodata` constants can be `static const` locals; a `const` word must follow the functions whose jump
  tables precede it. A C `.rodata` definition right before an `INCLUDE_ASM` whose asm carries `.rodata` makes GCC omit
  the next `.rdata` directive: avoid that order.
- Data objects are 4-aligned; small data and `.bss` start 8-aligned (`configure.py` inserts the `ALIGN(8)`).

### LOOP_BLOCK and LOOP_BARRIER
A loop's begin/end notes are scheduling barriers, and blocks leaving a loop are placed out of line. When a block matches
only inside `do { } while (0)`, use `LOOP_BLOCK(body)` or `LOOP_BARRIER()` (`include/common.h`) with a comment naming
the evidence class, found by compiling the macro form and the plain form:
- **A1:** identical with `-fno-schedule-insns` (a sched1 barrier). **A2:** identical only with
  `-fno-schedule-insns -fno-schedule-insns2` too (a post-reload reorder).
- **C:** still different with scheduling off, in instructions or layout: the loop pass puts a block out of line or
  reorg fills a delay slot differently.
- **B:** still different with scheduling off, but only in register names (references inside a loop count twice).
  The weakest evidence: first try the natural alternatives (case order, a duplicated tail, `return` for `break`, a
  fresh variable).
A bare `do { } while (0)` is not accepted.

### Forced (FAKE) matches
Only after natural C has been given up for that function. Mark the forced line with `/* FAKE: <what is forced and
why> */`. Forms in use elsewhere: a copy variable, mixed spellings of one access (`(p + i)->f` and `p[i].f`), a cast
chain, one variable reused for two jobs, a pointer computed from an index instead of stepped. `tools/hacks.py`
(CI's `check` job) fails on a `FAKE:` without its reason, a `LOOP_BLOCK` without its class, inline asm or `#if 0` in
game code.

## Search techniques

- **Siblings first:** copy the shape of an already matched function with the same logic (locals, re-fetched records,
  nested `if`s).
- **Hand searches that worked:** renaming variables across loops (one fresh variable per loop, declared first or last),
  case splitting and case order, hidden empty cases, duplicating tails per branch, statement-order hill-climbing,
  permuting declarations and types.
- **Mini reproductions:** a standalone C file with the function's shape (fake types), compiled with `tools/cc_psx.sh`
  and cut down until the choice flips, finds a scheduler or reorg cause in minutes.
- **Permuter:** a hint only, about 10 minutes per function, `-j1`; keep its output only if it reads as natural C.
  `import.py src/<t>/X.c asm/<t>/nonmatchings/X/func.s`. For allocation differences, raise the weights of
  `perm_temp_for_expr`, `perm_reorder_decls`, `perm_refer_to_var`; for a difference inside one basic block, permute a
  copy reduced to that block. Re-score its outputs with an instruction diff.

## Working in parallel

- Several people or agents on one machine: `RMPG2_JOBS` limits `configure.py` and ninja.
- Never trust git's line merge on a big C unit two people edited: merge per function by address and compare each
  side's per-function objdump, also with `-DNON_MATCHING`.
- Hand in: functions matched (count and bytes per unit), WIPs with their score, functions not tried; names added;
  every change to a shared file; new facts (one line each); split evidence; the final build result and the last
  commit hash.
