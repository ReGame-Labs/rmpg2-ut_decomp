#ifndef PSYQ_LIBAPI_H
#define PSYQ_LIBAPI_H

/* Psy-Q libapi (kernel) functions the game calls, declared from the game's own code (no SDK header is used). */

long GetRCnt(unsigned long spec);
long SetRCnt(unsigned long spec, unsigned short target, long mode);
long StartRCnt(unsigned long spec);
void FlushCache(void);
void EnterCriticalSection(void);
void ExitCriticalSection(void);
long OpenEvent(unsigned long desc, long spec, long mode, long (*func)());
long EnableEvent(unsigned long event);

#endif /* PSYQ_LIBAPI_H */
