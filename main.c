#include "utilis.h"
#include "scheduler.h"
#include <umps/libumps.h>

int main(){

init(); /* Funzione definita in utilis che inizializza le new area e i 3 processi */
scheduler();
HALT();
return(0);
	
}
