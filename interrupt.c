#include "interrupt.h"


extern pcb_t* current_proc;

int getLine(){
    //fare funzione che ritorni la linea di interrupt
}
void int_handler(){
    int line=getLine();
    if(line==9){
        setTIMER(-1);
        scheduler(ready_queue); //aggiustare sintassi per passare la lista
    }
}