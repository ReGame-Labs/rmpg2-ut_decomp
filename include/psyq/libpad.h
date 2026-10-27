#ifndef PSYQ_LIBPAD_H
#define PSYQ_LIBPAD_H

/* Psy-Q libpad functions the game uses, declared from the game's own code (no SDK header is used). */

void PadInitMtap(unsigned char *buf1, unsigned char *buf2);
void PadStartCom(void);
void ChangeClearPAD(long val);
int PadGetState(int port);
void PadSetAct(int port, unsigned char *table, int len);
int PadSetActAlign(int port, unsigned char *table);

#endif /* PSYQ_LIBPAD_H */
