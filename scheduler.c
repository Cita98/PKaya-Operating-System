#include "scheduler.h"

pcb_t* current_proc = NULL;
extern void log_process_order(int process);
extern struct list_head* head_rd;

void scheduler()
{
	/* Prendo il processo con priorità maggiore */
	current_proc = removeProcQ(head_rd);
	log_process_order(current_proc->original_priority);
	/* Controllo se la lista è vuota, nel caso metto in attesa */
	if (current_proc != NULL){
	/* Riporto la priorità del processo a quella originaria */
	current_proc->priority = current_proc->original_priority;
	/* Aumento la priorità di tutti gli altri processi che restano in coda */
	aging();
	/* Reimposto il timer */
	setTIMER(TIME_SLICE);
	/* Imposto lo stato del processore */
	setSTATUS(getSTATUS()|1);
	/* Carico lo stato del processo all'interno del processore */
	LDST(&(current_proc->p_s));
	}
	else{HALT();}
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
