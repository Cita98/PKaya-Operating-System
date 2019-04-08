#include "pcb.h"
#include "asl.h"
#include "const.h"
#include "types.h"
#include "p1.5test_rikaya.c"
#include "myConst.h"
#include "handler.h"

/* Variabili*/

int processCount; //contatore dei processi 
struct list_head readyQueue; //coda processi ready; 
pcb_t *currentProcess[MAX_CPU]; //puntatore al processo in esecuzione
state_t scheduler_state[MAX_CPU] //state_t dello scheduler

//PROCESSI DI TEST
extern void test1();
extern void test2();
extern void test3();


int main(){

/*inizializzo le new area*/

/***************************** INIT CPU0 */
    ((state_t *)INT_NEWAREA)->pc_epc = ((state_t *)INT_NEWAREA)->reg_t9 = (memaddr)int_handler;
    ((state_t *)INT_NEWAREA)->reg_sp = RAMTOP;
    ((state_t *)INT_NEWAREA)->status = EXCEPTION_STATUS;


    ((state_t *)SYSBK_NEWAREA)->pc_epc = ((state_t *)SYSBK_NEWAREA)->reg_t9 = (memaddr)syscall_handler;
    ((state_t *)SYSBK_NEWAREA)->reg_sp = RAMTOP;
    ((state_t *)SYSBK_NEWAREA)->status = EXCEPTION_STATUS;


/* chiamo la funzione initPcbs()*/
initPcbs();


/*creo la ready queue*/

LIST_HEAD(ready_queue);


/***********AGGIUNTA PROCESSI*/
/* come ha fatto il ragazzo
	//test1
	pcb_t* p1 = allocPcb();
	STST(&(p1->p_s));
	p1->p_s.pc_epc = p1->p_s.reg_t9 = (memaddr)test1;
	p1->p_s.reg_sp = PFRAMES_START;
	p1->p_s.status = PROCESS_STATUS;
	addReady(p1);
	
	
	//test2
	pcb_t* p2 = allocPcb();
	STST(&(p2->p_s));
	p2->p_s.pc_epc = p2->p_s.reg_t9 = (memaddr)test2;
	p2->p_s.reg_sp = PFRAMES_START-FRAME_SIZE;
	p2->p_s.status = PROCESS_STATUS;
	addReady(p2);
	
	
	//test3
	pcb_t* p3 = allocPcb();
	STST(&(p3->p_s));
	p3->p_s.pc_epc = p3->p_s.reg_t9 = (memaddr)test3;
	p3->p_s.reg_sp = PFRAMES_START-2*FRAME_SIZE;
	p3->p_s.status = PROCESS_STATUS;
	//~ debug(2, prova3);
	addReady(p3);
*/

// come farei io e come ha consigliato il tutor
pcb_t* p1=allocPcb();
LDST(p1->p_s); // non so se serve mettere & prima
//poi immagino bisogni fare questo
p1->p_s.pc_epc = p1->p_s.reg_t9 = (memaddr)test1;
p1->p_s.reg_sp = PFRAMES_START;  //costante non definita
p1->p_s.status = PROCESS_STATUS; //costante non definita

}
