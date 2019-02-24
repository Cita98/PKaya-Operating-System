#include "asl.h"
#include "pcb.h"

HIDDEN semd_t semd_table[MAXPROC];
LIST_HEAD(semd_h); /* Elemento sentinella della lista ASL */
LIST_HEAD(semdFree_h); /* Elemento sentinella della lista dei SEMD liberi o inutilizzati (semdFree) */


/* -------------------- FUNZIONE 14 -------------------- */

semd_t* getSemd(int *key)
{
	semd_t* Iter_Semd; /* Puntatore a semd, usato come iteratore della lista ASL */
 	
	if(!list_empty(&semd_h)) /*Se la ASL non è vuota */
	{ list_for_each_entry(Iter_Semd, &semd_h, s_next) /* Scorro la lista ASL */
	  { if(Iter_Semd->s_key == key){ return Iter_Semd;}} /* Se il semd corrente contiene la key cercata ritorno il suo puntatore */
	}
	return NULL; /* Altrimenti, se la lista è vuota oppure se non trovo il semd con la key cercata, ritorno NULL */
}


/* -------------------- FUNZIONE 15 -------------------- */

int insertBlocked(int *key, pcb_t* p) {
	semd_t *s = getSemd(key);

	if (s != NULL) {
		insertProcQ(&s->s_procQ, p);
		p->p_semkey = key;
		return FALSE;
	}

	if (list_empty(&semdFree_h)) {
		return TRUE;
	}
	
	s = container_of(semdFree_h.next, semd_t, s_next);
	list_del(semdFree_h.next);

	INIT_LIST_HEAD(&s->s_next);
	INIT_LIST_HEAD(&s->s_procQ);
	s->s_key = key;

	insertProcQ(&s->s_procQ, p);

	semd_t *list_s;
	list_for_each_entry(list_s, &semd_h, s_next) {
		if (s->s_key > list_s->s_key) {
			list_add(&s->s_next, &list_s->s_next);
			p->p_semkey = key;
			return FALSE;
		}
	}

	list_add(&s->s_next, &semd_h);
	p->p_semkey = key;
	return FALSE;
}


/* -------------------- FUNZIONE 16 -------------------- */

pcb_t* removeBlocked(int *key)
{
	pcb_t* procQ_removed; /* Processo da rimuovere */
	semd_t* ASL_Semd = getSemd(key); /* Memorizzo il puntatore al semd con quella key se è presente nella ASL, altrimenti ASL_Semd sarà NULL */
	if(ASL_Semd == NULL){return NULL;} /* Se il semd cercato non è tra quelli attivi ritorno NULL */
	    else /*Altrimenti*/
	   {    /* Rimuovo il primo processo dalla lista di quelli bloccati al semd e ne memorizzo il puntatore */
		procQ_removed = removeProcQ(&(ASL_Semd->s_procQ)); 
		/* Se la lista dei processi bloccati al semaforo diventa vuota */
		if(list_empty(&(ASL_Semd->s_procQ)))
		{   /* Rimuovo il semd dalla ASL */  
		    list_del(&(ASL_Semd->s_next));
                    /*Lo aggiungo alla semdFree */
		    list_add_tail(&(ASL_Semd->s_next), &semdFree_h);
                }
		/* Ritorno il puntatore al processo rimosso */
		return procQ_removed;
           }
}


/* -------------------- FUNZIONE 17 -------------------- */

pcb_t* outBlocked(pcb_t* p)
{
    /* Estraggo la chiave del semaforo in cui è bloccato il processo */
    int *semKey = p->p_semkey;
    /* Estraggo il puntatore al semd */
    semd_t* pSem = getSemd(semKey);
    /* Se il semaforo non esiste nella ASL ritorno NULL */
    if (pSem == NULL) {return NULL;}
          else
	  {
		/* Dobbiamo verificare che p sia presente nella coda di pSem */
    		/* Inizializzo l'elemento corrente per il ciclo for */
		struct list_head* cur;
    		list_for_each(cur, &(pSem->s_procQ)){
		/* Estraggo l'indirizzo del contenitore dell'elemento corrente */	
                pcb_t* curPcb = container_of(cur, pcb_t, p_next);
                /* Se l'elemento è quello che cerco */
                if (curPcb == p)
                {    /* Rimuovo l'elemento dalla coda dei processi bloccati del semd */
                     list_del(cur);
                     /* Ne ritorno l'indirizzo */
                     return p;
                }
           }
    /* Se non c'è ritorno NULL */
    return NULL;
}


/* -------------------- FUNZIONE 18 -------------------- */
    
}

pcb_t* headBlocked(int *key)
{
	semd_t* ASL_Semd = getSemd(key); /* Ottengo il semd corrispondente alla chiave se quest'ultimo è presente nella lista dei semd attivi, altrimenti ottengo NULL */
	/* Se il semd cercato non è presente nella ASL oppure se la sua coda dei processi è vuota */
	if(ASL_Semd == NULL || list_empty(&(ASL_Semd->s_procQ))){ return NULL;} /* Ritorno NULL */
	else
	{   /* Ritorno il puntatore al pcb che si trova in testa alla coda */
	    return (headProcQ(&(ASL_Semd->s_procQ)));
	}
} 


/* -------------------- FUNZIONE 19 -------------------- */

void outChildBlocked(pcb_t* p)
{
	/* Caso base: p non ha figli */
	if (!list_empty(&(p->p_child))){
		/* Caso ricorsivo/induttivo */
		struct list_head* childIt = &(p->p_child);
		/* scorro su ogni figlio */
		list_for_each(childIt, &(p->p_child))
		{
			pcb_t* curPcb = container_of(childIt, pcb_t, p_sib);
			/* elimino i processi figli */
			outChildBlocked(curPcb);
		}
	}
	/* Infine rimuovo il processo originario */
	p = outBlocked(p);	
}


/* -------------------- FUNZIONE 20 -------------------- */


void initASL(){
	
	int i; /* Iteratore */
	INIT_LIST_HEAD(&(semd_h));
	INIT_LIST_HEAD(&(semdFree_h));
	/* Fino al numero massimo di processi */
	for (i=0; i < MAXPROC; i++)
	{	/* Inizializzo i campi della semd_table */
		semd_t* newSemdEl = &semd_table[i];
		/*mkEmptyProcQ(&(newSemdEl->s_procQ));*/
		/* Aggiungo ogni descrittore della semd_table alla semdFree */
		list_add_tail(&(newSemdEl->s_next), &(semdFree_h));
	}	
}



