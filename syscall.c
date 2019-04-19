#include "syscall.h"

void TerminateProcess(struct list_head* head_rd)
{
	/* Rimuovo il processo da terminare dalla ready queue */
	pcb_t* current = removeProcQ(head_rd);
	/* Rimuovo anche tutti i suoi figli, prima o poi lo farò */
	
}
