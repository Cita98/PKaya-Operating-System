#include "scheduler.h"
#include "pcb.h"

pcb_t* current_proc = NULL;

void Scheduler(struct list_head* head_rq)
{
	/* Prendo il processo con priorità maggiore */
	current_proc = removeProcQ(head_rq);
	log_processor_order(current_proc->original_priority);
	/* Controllo se la lista è vuota, nel caso metto in attesa */
	if (current_proc =! NULL){
	/* Riporto la priorità del processo a quella originaria */
	current_proc->priority = current_proc->original_priority;
	/* Aumento la priorità di tutti gli altri processi che restano in coda */
	aging(head_rq);
	/* Reimposto il timer */
	setTIMER(TIME_SLICE);
	/* Carico lo stato del processo all'interno del processore */
	LDST(&(current_proc->p_s));
	}
	else{HALT();}
}

void Context_Switch(struct liste_head* head_rq)
{    
	if(current_proc =! NULL){
	/* Reinserisco il processo corrente (se esiste) nella lista dei processi pronti */
	insertProcQ(head_rq, current_proc);
	}
	/* Prendo il prossimo processo in lista e lo carico, richiamando la funzione dello scheduler */
	Scheduler(head_rq);
	
}

void aging(struct list_head* head_rq)
{
	/* Creo l'iteratore della lista ready queue */
	struct list_head* iter = head_rq->next;
	/* Scorro la lista e aumento di 1 la priorità di ogni processo */
	list_for_each_entry(iter, head_rq, p_next)
	{ iter->priority = iter->priority+1; }
}
