#ifndef INTERRUPT_H
#define INTERRUPT_H

#include <umps/libumps.h>

/* Costanti per le linee di interrupt */

#define INT_LOCALTIMER 2

int getBit(int shift, unsigned int reg);
int getINT_LINE();

#endif
