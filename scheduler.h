#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "listx.h"
#include "pcb.h"
#include "utilis.h"
#include <umps/libumps.h>

void scheduler(); // Prende il processo con priorità più alta dalla lista dei processi pronti e lo carica nel processore
void context_switch(); // Cambia il processo corrente rimettendolo nella coda dei processi pronti, richiama scheduler
void aging(); // Aumenta le priorità dei processi nella ready_queue quando questi non vengono scelti

#endif


