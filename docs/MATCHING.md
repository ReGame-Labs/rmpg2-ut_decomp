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
| `tools/draft.py <func> [-t <target>]` | A typed m2c draft: m2c with the function's unit, preprocessed as the build does and reduced to its declarations, as its context; `--sweep <unit>` drafts and scores every `INCLUDE_ASM` function of a unit without editing it |
| m2c (`tools/ext/m2c`) | By hand: `m2c.py --target mipsel-gcc-c --context <ctx.h> asm/<t>/nonmatchings/<unit>/<func>.s` (`draft.py --context` prints a unit's) |
| `tools/compiler_id.py` | m2c drafts of a whole target, compiled with every GCC, scored; the exact ones are free matches |
| `tools/unit_diff.py <unit> [func] [-t <target>] [-D NON_MATCHING]` | Checks one C unit against the original as the link would write it, per function and data section, and says whether the unit links to the original bytes; no ninja, parallel-safe; with a function, a side-by-side instruction diff |
| `tools/variant.py get/put/try/perm <func> [file]` | The loop's scorer: puts C in place of a function in a copy of its unit and scores it with unit_diff's comparison (`put`), ranks variants (`try`), compiles every order of marked lines (`perm`); writes the unit only to keep a candidate, as C when it matches or as a WIP block (`--wip`) |
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
- A constant built with `lui` + `addiu`/`ori` that spimdisasm pairs into a symbol of its own (`D_7FFFFF`, `D_12D00`)
  makes the matching C score below 100 %: list it in the symbol file with `// ignore:true` and the pair stays numbers.
- Several names for one address (the original's distinct symbols that the link placed together): splat takes one
  name per address, so the extra names go in `config/aliases.ld` as `other_name = name;` lines, a linker-script
  fragment the executable's link reads; the C uses the names the original did.
- `main` is compiled as `game_main`, and `config/aliases.ld` gives it its name (`main = game_main;`). GCC 2.8.1
  starts any function named `main` with `jal __main` (cc1 calls it to run global constructors on targets without
  init sections), and the original's `main` has no such call. Nothing in the build references `main` by symbol:
  crt0, kept as data, calls `0x8001781C` with a literal `jal` word.
- `permuter_settings.toml` compiles at `-G 0`; set the file's `-G` there when permuting a function of another file.

## The loop per function

1. **Draft** with `tools/draft.py <func>`: m2c with the unit's own declarations as its context, so the draft has the
   unit's types, struct fields, globals and prototypes (some drafts with real types match as drafted). `draft.py
   --sweep <unit>` drafts every `INCLUDE_ASM` function of a unit into `build/draft/<t>/<unit>/` and scores each in a
   copy of the unit; the `compiler_id.py` drafts are the untyped alternative. Turn the draft into natural C: no
   `M2C_` macros, real fields for `M2C_FIELD`. m2c misreads arguments of calls through function pointers (check
   `a2`/`a3` and stack stores in the asm) and its store order is not source order.
2. **Score** with `tools/variant.py put <func> <file.c>`. It puts the C in place of the function (its `INCLUDE_ASM`,
   its C or its WIP block) in a copy of the unit under `build/variant/`, compiles the unit as the build does and
   checks it with `unit_diff.py`'s comparison; `-s` adds the side-by-side diff. The unit's file changes only when
   the C matches: the function passes and the whole unit links to the original bytes. `variant.py get <func>` prints
   a function's C (a WIP's C), the start of a variants file.
   - A C function is `OK` when its size is the original's and every instruction is the original's word once linked
     (relocations and branch targets resolved to addresses, the names `config/aliases.ld` gives one address
     included), its jump table too; `OK (by address)` when objdiff scores it below 100% while the linked words are
     the same (a relocation naming another symbol for the same address, a constant the original's asm has as a
     symbol). A function that differs shows objdiff's score (the number to raise) and what differs: its size, the
     first differing instruction, its jump table.
   - `tools/unit_diff.py <unit> [func]` checks the unit's file as it is: every function's result, and on its last
     line and in its exit status whether the unit links to the original bytes (every function at its original
     offset with its original size, the bytes between them, the data sections the C provides).
   - The ranking is that comparison's, never a diff count over aligned disassembly (an alignment can make a
     function of another size or order look one instruction away). The build stays the proof: unit_diff sees one
     unit, not the `.bss` the C defines, the other units or a symbol-file change.
3. **Iterate on natural C**: types, struct fields, statement order, a variable per job (the patterns below). Look for
   an already matched sibling first.
   - `variant.py try <func> <file>` scores the variants of one file, separated by `//---` lines, and ranks them;
     `-k N` keeps variant N (with `--wip` when it does not match).
   - `variant.py perm <func> <file>` compiles every order of the lines marked `//@P` (sets `//@P2`, ... are permuted
     independently) times every choice among the alternatives marked `//@G<name>` (a bare `//@G1` is the empty
     alternative), stops at the first match and writes the best to `build/variant/`. The marker starts the line
     (`//@P a->x = 0;`) or ends it (`a->x = 0; //@P`). Up to `--max` candidates (5040), sampled beyond; `-j` compiles
     in parallel (`RMPG2_JOBS`); `-k` keeps the best.
4. **Stop** after about 30-45 minutes on one function: `variant.py put <func> <file.c> --wip [--note "..."]` writes
   the C under `#ifdef NON_MATCHING` with the `INCLUDE_ASM` in the `#else` and a comment with the score and the
   remaining difference (the note; else the block's old note; else what unit_diff reports). It writes the block only
   when the unit still links and the C compiles with `-DNON_MATCHING` (`unit_diff.py <unit> -D NON_MATCHING` scores
   every WIP of a unit).
5. **Build and commit** every ~10 matches: `scripts/build.sh` must say "build passed" (`--check` after config or symbol
   changes).

Both tools find the function's unit under `src/` (`-t <target>` for an overlay's, `-u <unit>` to name it), take the
compiler and `-G` from `configure.py` (the GCC 2.7.2 units included) and handle K&R definitions. They compile one
unit, without ninja, so several sessions can use them while others build.

## Conventions

- **Names:** game functions and globals are `<module>_<verb>_<noun>` in snake_case, the prefix being the defining C
  file (`src/main/cdload.c` → `cdload_read_file`). Types PascalCase (`<Module><Noun>`), constants
  `MODULE_UPPER_SNAKE`, unknown fields `unk_<offset>`, alignment padding `pad_<offset>`. Only what is understood is
  named; otherwise splat's `func_<addr>`/`D_<addr>`. An original name found in the binary wins; Psy-Q names stay
  Sony's. Rename everywhere at once (`grep -rn` over `src/ include/ config/`).
- **Files:** each C file is a module named from its code, the name the original would have had (`building.c`,
  `monster.c`; the sound driver's parts `wess.c`, `wess_seq.c`, `wess_spu.c`), its header `include/<module>.h`. A file
  whose code does not tell yet keeps the address of its first function (`game_8004C064.c`); a wrong name is worse
  than an address. Renaming a file renames its splat subsegment, its header, its `#include`s, its `CC_OVERRIDES`
  entry and its `// <module>` block in the symbol file together. The list: [`DISC_LAYOUT.md`](DISC_LAYOUT.md) "The
  files".
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
- **Overlay padding:** in `OVERATTR.BIN` each game object's `.rodata` and `.text` start 8-aligned, so a zero word
  after a function's last instruction, or an unused `""`/zero word before the next file's first string, is a file
  boundary (`configure.py` `align_overlay_sections` inserts the `ALIGN(8)`). Where the previous object already ends
  8-aligned the boundary leaves no trace.
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
- Callers that load `a0` for a callee that never reads it: the callee keeps an unused parameter (`func_8002107C(Ai *)`).
- Callers that pass fewer arguments than the callee reads: the callee is a K&R definition with no prototype in scope
  (`func_80031154(kind, m)`).
- A result masked with `andi 0xFFFF` after every call: the callee returns `u16` (`func_80038C1C`). A call with no
  prototype in scope returns `int` and loses the mask.

### Structs, globals and aliasing
- GCC 2.8 assumes a struct field and a scalar global never alias. A global reloaded after a struct-field store is a
  struct member: make it a one-member struct (`D_801FB190` in `func_8002A3A4`; also for a function-pointer global
  called right after such stores).
- One global can be reached both through its struct (`D_800AA248.cur_obj`) and as a symbol of its own
  (`D_800AA268.p`): the relocation's symbol says which form each access used, and the struct form keeps a field store
  ordered before a later load (`func_80039D04`).
- A word read with `lw` in one place and as a halfword at +2 in another is a union: `Fixed`'s `.w`, `.s.hi`, `.u.hi`
  (`func_800346FC`).
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
- A stepped pointer (`p = table; p += k - 1; *p`) gives `addu base,index` where `table[k - 1]` gives `addu
  index,base` (`func_8002DAAC`).
- `handler = &T[i]; (*handler)(x)` puts base and index in the other order than `T[i](x)` (`func_80026C04`). With the
  index from a call, `i = f(); T[i & 7]()` computes the index first; `T[f() & 7]()` keeps the table base in a saved
  register (`func_8003C0E8`).
- A mask or wrap written stepwise keeps its `and`: `x = pos; x += vel; x &= w; pos = x;` (`func_80044F08`); the
  single expression folds it.
- `abs()` is a call to `s32 abs(s32)` (`func_80039D04`). Inline, `d >= 0 ? d : -d` negates a copy (`move` + `negu`)
  and `if (d < 0) d = -d;` negates in place (`func_80023CFC`).
- `if (c) v = -v; a = v + x;` puts a copy of the add in the delay slot after the `negu` (`func_80037960`).
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
- When the original copies a value just stored into a field, write the read through the field: `D_800AA248.new_def =
  f(); def = D_800AA248.new_def;` also puts the store right after the call (`func_80031364`).
- A local read before it is set shows as a read of a callee-saved register before the prologue saves it: the
  original's bug, kept with a comment (`func_80031074`).
- An `andi 0xFFFF` re-extending a counter before a call: the counter variable was reused for another value
  (`func_8004B540`).
- A pointer parameter whose `move` sits late in the prologue was copied into a typed local (`MenuRecord *menu =
  list;`, `func_8009DF98`).
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
- An object definition's positions are stored before its constant fields (`func_80017F14`). A load from another
  object comes before the stores into a new one, which may alias it: such store orders are found with `variant.py
  perm`.
- A statement placed after a call moves delay-slot fills; code after a branch can decide that branch's delay slot.
- Pass order: sched1 → … → sched2 → jump2 (cross-jumping) → reorg. Analyse tail merges in sched2's order.

### Switches and cross-jumping
- A jump table needs at least 5 case labels (5 sparse cases still gave a compare tree, 6 a table). `slti`+`bltz` range
  tests come from a switch with adjacent cases. Check the jump table before believing a fallthrough.
- Case bodies are emitted in source order: order cases as the original places them, but try numeric order first, since
  a case out of order can switch cross-jumping on or off.
- Hidden empty cases decide codegen: `case 0: break;` when the table starts at 0; `case 0: default:` in object
  `switch (state)`es; a `slti` in a `u8` switch tree means an explicit `case 0:` sharing the default; an unbalanced
  compare tree means an empty case whose test jump optimisation deleted (`case 0x240:` in `func_8001B858`).
- Two case values make a compare chain, three a tree; an unsigned switch value drops the range test; a 6-entry table
  can need its empty cases written out (`case 1: case 2: case 3: default:`, `card_write_save`). A 3-value switch
  after a range test is `if (k < 4) … else switch (k)`, one call per arm (`func_80031154`).
- An out-of-line stub jumping into a shared tail means the source wrote the tail in each branch: write the final call,
  `return` or clear per branch when the original has them per branch. A variable per case stops tail merging. Two
  arms calling one function, each with its own argument, are two calls, not a `?:` or a selector local
  (`func_80023CFC`).
- When both arms return, the source wrote the later block first: `if (id < 0) return id; return …;` (`func_8001B660`).
- Some layouts match only with the asm's block order written as labels and `goto`s (`func_8003FF54`). Invariants
  hoisted into an inner loop's preheader mean the outer loop was a label (`restart:` in `game_main`); a `goto retry`
  before an endless loop recomputes them (`cdload_read_file`).
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
- Countdown loops are `do { …; p++; } while (--n != 0)` with a `u16 n` (`func_8004B540`); a table scan is `while (*t
  != NULL) { if (*t == target) break; t++; }` (`func_80031280`).
- Operands read in sequence go through a stepped pointer: `p = obj->arg.h; a = *p++; b = *p;` (`func_800476FC`).
- A chained `a = b = c = 0` changes loop.c's hoisting against three stores (`game_main`).

### GCC 2.7.2 (the sound driver)
The units of `configure.py`'s `CC_OVERRIDES`. The patterns above hold unless one here says otherwise.
- A global counter `while (G-- != 0)` stores, then tests (`func_8006DBC0`); `G = x; while (--G != -1)` keeps both
  stores only with a statement between them.
- `x->f &= ~2; x->f &= ~8;` gives two `and`s and one store; a local folds them (`func_8006BB14`).
- `for (i = 0, p = table; …; i++, p++)` decides the loop's registers (`func_8006BF08`).
- `if (p != NULL) return x; return 0;` gives the `bnez` layout (`func_8006EC18`); `if (n < 0 || n >= N) return 0;
  return 1;` the branchy range check (`func_8006E504`).

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
- A unit's data stays in asm, declared `extern`, unless one of its functions cannot match otherwise: a computed goto
  whose `&&label` table is a `static` in `.data`, for example. Then the unit's `data` subsegment becomes `.data`, and
  the C defines every object of it in the original order (the table as the function's `static`, in its place).
  `.bss` can stay COMMON (no `DATA_IN_C` entry).

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
  case splitting and case order, hidden empty cases, duplicating tails per branch, statement-order searches (`variant.py perm`),
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
