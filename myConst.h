#ifndef MYCONST_H
#define MYCONST_H

/* Costanti */
#define RAMBASE *((unsigned int *)0x10000000)
#define RAMSIZE *((unsigned int *)0x10000004)
#define RAMTOP (RAMBASE + RAMSIZE)

/* definisco gli indirizzi delle new e old area */

#define INT_NEWAREA 0x2000008c
#define INT_OLDAREA 0x20000000
#define TLB_NEWAREA 0x200001a4
#define TLB_OLDAREA 0x20000118
#define PGMTRAP_NEWAREA 0x200002bc
#define PGMTRAP_OLDAREA 0x20000230
#define SYSCALL_NEWAREA 0x200003d4
#define SYSCALL_OLDAREA 0x20000348

#define FRAMESIZE 4096

#define TIME_SLICE 3000


#endif
