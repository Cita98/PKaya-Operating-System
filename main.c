#include "pcb.h"
#include "asl.h"
#include "const.h"
#include "types.h"
#include "p1.5test_rikaya.c"
#include "myConst.h"
#include "handler.h"


//PROCESSI DI TEST
extern void test1();
extern void test2();
extern void test3();


int main(){

/*inizializzo le new area*/

/***************************** INIT CPU0 */
    ((state_t *)INT_NEWAREA)->pc_epc = (memaddr)int_handler;
    ((state_t *)INT_NEWAREA)->reg_sp = RAMTOP;
    ((state_t *)INT_NEWAREA)->status = EXCEPTION_STATUS;

    ((state_t *)SYSCALL_NEWAREA)->pc_epc = (memaddr)syscall_handler;
    ((state_t *)SYSCALL_NEWAREA)->reg_sp = RAMTOP;
    ((state_t *)SYSCALL_NEWAREA)->status = EXCEPTION_STATUS;


    // questo non lo chiede ma dobbiamo comunque inizializzare 

    //((state_t *)TLB_NEWAREA)->pc_epc =(memaddr)tlb_handler;
	((state_t *)TLB_NEWAREA)->reg_sp = RAMTOP;
	((state_t *)TLB_NEWAREA)->status = EXCEPTION_STATUS;
	
	//((state_t *)PGMTRAP_NEWAREA)->pc_epc = (memaddr)pgmtrap_handler;
	((state_t *)PGMTRAP_NEWAREA)->reg_sp = RAMTOP;
	((state_t *)PGMTRAP_NEWAREA)->status = EXCEPTION_STATUS;

    


/* chiamo la funzione initPcbs()*/
initPcbs();


/*creo la ready queue*/

LIST_HEAD(ready_queue);

/*AGGIUNGO PROCESSI*/

/*processo1*/
pcb_t* p1=allocPcb();
LDST(p1->p_s); // non so se serve mettere & prima e non capisco perché il tipo lo mette prima se dopo cambia stato
p1->p_s.pc_epc = (memaddr)test1;
p1->p_s.reg_sp = RAMTOP-FRAMZESIZE*1;
p1->p_s.status = STATOPROC; 
p2->priority=1;
//aggiunto il processo nella lista ready
insertProcQ(ready_queue, p1) // forse da aggiustare la sintassi

/*processo2*/
pcb_t* p2=allocPcb();
LDST(p2->p_s); // non so se serve mettere & prima e non capisco perché il tipo lo mette prima se dopo cambia stato
p2->p_s.pc_epc = (memaddr)test1;
p2->p_s.reg_sp = RAMTOP-FRAMESIZE*2;  
p2->p_s.status = STATOPROC; 
p2->priority=2;
//aggiunto il processo nella lista ready
insertProcQ(ready_queue, p2) // forse da aggiustare la sintassi

/*processo3*/
pcb_t* p3=allocPcb();
LDST(p3->p_s); // non so se serve mettere & prima e non capisco perché il tipo lo mette prima se dopo cambia stato
p3->p_s.pc_epc = (memaddr)test1;
p3->p_s.reg_sp = RAMTOP-FRAMESIZE*3; 
p3->p_s.status = STATOPROC; 
p2->priority=3;
//aggiunto il processo nella lista ready
insertProcQ(ready_queue, p3) // forse da aggiustare la sintassi





}
