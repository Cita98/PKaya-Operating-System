#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "listx.h"
#include "pcb.h"
#include "utilis.h"
#include <umps/libumps.h>

void scheduler();
void context_switch();
void aging();

#endif


