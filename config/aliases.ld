/* Several names for one address of the executable: a linker-script fragment linked after the objects (configure.py,
 * Target "main"). The original gave different symbols to tables the link then placed at one address (empty tables
 * of a placeholder monster at 0x8008E6AC), and C that names them apart compiles differently from C that names them
 * once (GCC cross-jumps identical cases), so the C keeps the original's names and this file resolves them.
 * splat accepts one name per address in config/symbol_addrs.txt; the extra names live here, one line each, with
 * the function that needs them. Overlays get a config/<overlay>.aliases.ld the same way when they need one. */
