#include "syscall.h"

extern pcb_t* current_proc;
extern pcb_t ready_queue;  //non sicuro

void syscall_handler()
{
	state_t* old= (state_t*) SYSCALL_OLDAREA;

	//qui gli altri copiano anche lo stato della old area in pcb_t->p_s, non so se serve per forza

	/*incremento il pc (anche questo non so se serve)*/ 
	old->pc_epc+=4;

	if(old->reg_a0==SYS3){
		terminateProcess();
		scheduler(&(ready_queue.p_next));
	}else{
		adderrbuf("error");
	}



}


void terminateProcess(struct list_head* head_rd)
{
	/* Rimuovo il processo da terminare dalla ready queue */
	pcb_t* current = removeProcQ(head_rd);
	/* Rimuovo anche tutti i suoi figli, prima o poi lo farò */
	
}
