#include "handler.h"

extern pcb_t* current_proc;
extern void addokbuf();

void int_handler(){
	
	/* Prendo il puntatore allo stato del processo interrotto, nella old area */
	state_t* old_proc = ((state_t*)INT_OLDAREA);
	/* Copio lo stato del processo interrotto nel processo corrente */
	cp_state(old_proc, &(current_proc->p_s));
	
	int int_line = getINT_LINE();
	
	switch(int_line)
	{
			case(9):
			/* Ack dell'interrupt, riavvio il timer */
			addokbuf("INTERRUPT PRESO");
			setTIMER(TIME_SLICE);
			/* Richiamo lo scheduler per far partire il prossimo processo */
			context_switch();
			break;
			
			default: /*In tutti gli altri casi, errore */
			addokbuf(" INTERRUPT ERROR ");
			break;
			
	}

}

void syscall_handler()
{
	/* Prendo il puntatore allo stato del processo interrotto, nella old area */
	state_t* old_proc =((state_t*) SYSCALL_OLDAREA);
	/* Copio lo stato del processo interrotto nel processo corrente */
	cp_state(old_proc, &(current_proc->p_s));

	switch(current_proc->p_s.reg_a0)
	{
			case(SYS3):
			/* Termino il processo corrente e tutta la sua progenie */
			addokbuf("SYSTEM CALL PRESA");
			terminate_process(current_proc);
			/* Richiamo lo scheduler per passare al prossimo processo */
			scheduler();
			
			default:
			addokbuf(" SYSTEMCALL ERROR ");
			break;
	}



}



