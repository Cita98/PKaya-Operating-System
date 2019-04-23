#include "syscall.h"

void terminate_process(pcb_t* current_proc)
{
	/* Rimuovo il processo da terminare e tutti i suoi figli dalla ready_queue */
	outChildBlocked(current_proc);
	/* NOTA: Il processo terminato non si troverà sicuramente nella ready_queue poichè era il processo corrente */
	/* Libero il processo corrente rimettendolo nella lista dei pcb liberi */
	freePcb(current_proc);
}
