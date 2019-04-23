#include "utilis.h"

/* Lista dei processi pronti, dichiarata qui per poterla richiamare e condividere in tutti gli altri file */
LIST_HEAD(ready_queue);
struct list_head* head_rd = &(ready_queue);

//PROCESSI DI TEST
extern void test1();
extern void test2();
extern void test3();


void init(){

    /*inizializzo le new area*/

        ((state_t *)INT_NEWAREA)->pc_epc = (memaddr)int_handler;
        ((state_t *)INT_NEWAREA)->reg_sp = RAMTOP;
        ((state_t *)INT_NEWAREA)->status = EXCEPTION_STATUS;

        ((state_t *)SYSCALL_NEWAREA)->pc_epc = (memaddr)syscall_handler;
        ((state_t *)SYSCALL_NEWAREA)->reg_sp = RAMTOP;
        ((state_t *)SYSCALL_NEWAREA)->status= EXCEPTION_STATUS;


		
        // questo non lo chiede ma dobbiamo comunque inizializzare nella prossima fase

        /*((state_t *)TLB_NEWAREA)->pc_epc =(memaddr)tlb_handler;
        ((state_t *)TLB_NEWAREA)->reg_sp = RAMTOP;
        ((state_t *)TLB_NEWAREA)->status = EXCEPTION_STATUS;
        
        ((state_t *)PGMTRAP_NEWAREA)->pc_epc = (memaddr)trap_handler;
        ((state_t *)PGMTRAP_NEWAREA)->reg_sp = RAMTOP;
        ((state_t *)PGMTRAP_NEWAREA)->status = EXCEPTION_STATUS;*/

        

    /* chiamo la funzione initPcbs()*/
    initPcbs();
	
    /*inizializzo la ready queue*/
    mkEmptyProcQ(&(ready_queue));

    /*AGGIUNGO PROCESSI*/

    /*processo1*/
    pcb_t* p1=allocPcb();
    p1->p_s.pc_epc = (memaddr)test1;
    p1->p_s.reg_sp = RAMTOP-FRAMESIZE*1;
	
	p1->p_s.status = STATOPROC;
    p1->priority=1;
	//p1->original_priority = 1;
    //aggiunto il processo nella lista ready
    insertProcQ(&(ready_queue), p1); // forse da aggiustare la sintassi

    /*processo2*/
    pcb_t* p2=allocPcb();
    p2->p_s.pc_epc = (memaddr)test2;
    p2->p_s.reg_sp = RAMTOP-FRAMESIZE*2;  
    p2->p_s.status = STATOPROC; 
    p2->priority=2;
	p2->original_priority = 2;
    //aggiunto il processo nella lista ready
    insertProcQ(&(ready_queue), p2); // forse da aggiustare la sintassi

    /*processo3*/
    pcb_t* p3=allocPcb();
    p3->p_s.pc_epc = (memaddr)test3;
    p3->p_s.reg_sp = RAMTOP-FRAMESIZE*3; 
    p3->p_s.status = STATOPROC; 
    p3->priority=3;
	p3->original_priority = 3;
    //aggiunto il processo nella lista ready
    insertProcQ(&(ready_queue), p3); // forse da aggiustare la sintassi

}

void cp_state(state_t* src_state, state_t* dst_state)
{
	/* Copio ogni campo dello stato sorgente nello stato di destinazione */
	dst_state->entry_hi = src_state->entry_hi;
	dst_state->cause = src_state->cause;
	dst_state->status = src_state->status;
	dst_state->pc_epc = src_state->pc_epc;
	dst_state->hi = src_state->hi;
	dst_state->lo = src_state->lo;
	for(int i=0;i<29;i++){dst_state->gpr[i]=src_state->gpr[i];}
	
}
