
#ifndef MYCONST_H
#define MYCONST_H

/* definisco gli indirizzi delle new e old area */

#define INT_NEWAREA 0x2000008c
#define INT_OLDAREA 0x20000000
#define TLB_NEWAREA 0x200001a4
#define TLB_OLDAREA 0x20000118
#define PGMTRAP_NEWAREA 0x200002bc
#define PGMTRAP_OLDAREA 0x20000230
#define SYSCALL_NEWAREA 0x200003d4
#define SYSCALL_OLDAREA 0x20000348

/*definisco costante per  exeption status: interrupt mascherati
VM off ,  PLT  ON e kernel mode*/

#define EXCEPTION_STATUS 00011000000000000000000000000001

/*definisco costanti per stato dei processi*/
#define STATOPROC 00011000000000001111111100000100

#define FRAMESIZE 4096

#define TIME_SLICE 3000

#define SYS3 3


#endif MYCONST_H
