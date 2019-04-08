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

/*aggiungo processi*/

// come farei io e come ha consigliato il tutor
pcb_t* p1=allocPcb();
LDST(p1->p_s); // non so se serve mettere & prima
//poi immagino bisogni fare questo come il tipo
p1->p_s.pc_epc = p1->p_s.reg_t9 = (memaddr)test1;
p1->p_s.reg_sp = PFRAMES_START;  //costante non definita
p1->p_s.status = PROCESS_STATUS; //costante non definita

list_add_tail(pcb_t* p1, ready_queue* head); //da aggiustare la sintassi

}
