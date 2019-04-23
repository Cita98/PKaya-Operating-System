#ifndef UTILIS_H
#define UTILIS_H

#include "pcb.h"
#include "listx.h"
#include "myConst.h"
#include "handler.h"
#include <umps/cp0.h>

void init(); // Funzione che inizializza il sistema
void cp_state(state_t* scr_state, state_t* dst_state); // Funzione che copia lo stato corrente nello stato di destinazione

#endif