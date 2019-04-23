#ifndef SYSCALL_H
#define SYSCALL_H

#include "asl.h"
#include "pcb.h"

/* Definisco costanti per il riconoscimento del tipo di systemcall */
#define SYS3 3

void terminate_process(pcb_t* current_proc); // Termina il processo corrente e tutti i processi figli

#endif
