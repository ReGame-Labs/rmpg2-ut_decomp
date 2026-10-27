#ifndef PSYQ_LIBMCRD_H
#define PSYQ_LIBMCRD_H

/* Psy-Q libmcrd (the memory-card functions) the game calls, declared from the game's own code (no SDK header is
 * used). MemCardSync returns 0 while the command runs, 1 when it is done (*cmd the command, *result its result),
 * -1 when no command is pending. */

long MemCardSync(long mode, long *cmd, long *result);
long MemCardExist(long chan);
long MemCardAccept(long chan);
long MemCardReadFile(long chan, char *name, void *buf, long offset, long size);
long MemCardWriteFile(long chan, char *name, void *buf, long offset, long size);
long MemCardCreateFile(long chan, char *name, long blocks);
long MemCardFormat(long chan);

#endif /* PSYQ_LIBMCRD_H */
