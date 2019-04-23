#ifndef INTERRUPT_H
#define INTERRUPT_H

#include <umps/libumps.h>

/* Costanti per le linee di interrupt */

#define INT_LOCALTIMER 0

int getINT_LINE(); /* Funzione per riconoscere la linea che ha generato l'interrupt */

#endif
