# Psy-Q interface declarations

Our own declarations of the Psy-Q library interface the game calls (`libgpu.h`, `libgte.h`, `libcd.h`, ...), one
header per library, written from the game's own code as functions get matched. No file of the SDK is used or
copied; Sony's names are kept (`DrawSync`, `RECT`, `POLY_FT4`) because the game's code calls them by those names.
