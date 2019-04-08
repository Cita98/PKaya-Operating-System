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



}
