#ifndef FUN_UTILI_H
#define FUN_UTILI_H

#include "types_rikaya.h"

/**************************************************************************** 
 *
 * This header file contains: Funzioni utili per le varie implementazioni
 *
 ****************************************************************************/

/******************* FUNZIONI PER PCB *************************/

/* Inizializza stato */

static inline void INIT_STATE( state_t* state)
{
	int i; /* Counter */
    state->entry_hi = 0;
    state->cause = 0;
    state->status = 0;
    state->pc_epc = 0;
    /* scorro tutti i registri */
    for (i = 0; i<29; i++)
        state->gpr[i] = 0;
    state->hi = 0;
	state->lo = 0;
	
}



#endif
