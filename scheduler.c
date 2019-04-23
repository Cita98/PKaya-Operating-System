#include "scheduler.h"

pcb_t* current_proc = NULL;
extern void log_process_order(int process);
extern struct list_head* head_rd;

void scheduler()
{
	/* Prendo il processo con priorità maggiore */
	current_proc = removeProcQ(head_rd);
	log_process_order(current_proc->original_priority);
	/* Controllo se la lista dei processi pronti è vuota,se non lo è */
	if (current_proc != NULL){
	/* Riporto la priorità del processo a quella originaria */
	current_proc->priority = current_proc->original_priority;
	/* Aumento la priorità di tutti gli altri processi che restano in coda */
	aging();
	/* Imposto il local timer */
	setTIMER(TIME_SLICE);
	/* Carico lo stato del processo all'interno del processore */
	LDST(&(current_proc->p_s));
	}
	else{HALT();} // Se la ready_queue è vuota metto il sistema in attesa
}

void context_switch()
{    
	if(current_proc != NULL){
	/* Reinserisco il processo corrente (se esiste) nella lista dei processi pronti */
	insertProcQ(head_rd, current_proc);
	}
	/* Prendo il prossimo processo in lista e lo carico, richiamando la funzione dello scheduler */
	scheduler();
	
}

void aging()
{
	/* Creo l'iteratore della lista ready queue */
	pcb_t* iter;
	/* Scorro la lista e aumento di 1 la priorità di ogni processo */
	list_for_each_entry(iter, head_rd, p_next)
	{ iter->priority = iter->priority+1; }
}
