/* Several names for one address of the executable: a linker-script fragment linked after the objects (configure.py,
 * Target "main"). The original gave different symbols to tables the link then placed at one address (empty tables
 * of a placeholder monster at 0x8008E6AC), and C that names them apart compiles differently from C that names them
 * once (GCC cross-jumps identical cases), so the C keeps the original's names and this file resolves them.
 * splat accepts one name per address in config/symbol_addrs.txt; the extra names live here, one line each, with
 * the function that needs them. Overlays get a config/<overlay>.aliases.ld the same way when they need one. */

/* func_8002C32C (game_8002A330): the animation for an actor of kind 2 and for the others, one table at 0x8001236C. */
D_8001236C_alt = D_8001236C;
/* func_80043C0C, func_80043CC0, func_80043D74 (game_80043118): one name per range class of func_8004A468. */
D_8008E6AC_1 = D_8008E6AC;
D_8008E6AC_2 = D_8008E6AC;
D_8008E6AC_3 = D_8008E6AC;
D_8008E6AC_4 = D_8008E6AC;
/* func_8003047C (game_8002A330): the animation for the random draws 0-1 and 3, one table at 0x8001214C. */
D_8001214C_alt = D_8001214C;
