#include "pcb.h"

LIST_HEAD(pcbFree_h); /*Dichiarazione e inizializzazione nuova lista*/
HIDDEN pcb_t pcbFree_table[MAXPROC];

/* Funzione ausiliaria che inizializza il campo state */

static inline void INIT_STATE(state_t* state)
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


/* -------------------- FUNZIONE 1 -------------------- */

void initPcbs(void)
{
     int i; /* Counter */
    /* Inizializzazione della sentinella */
    INIT_LIST_HEAD(&(pcbFree_h));

    /* Inizializzazione della lista pcbFree */
    for (i = 0; i < MAXPROC; i++)
    {
	/* Creo un nuovo puntatore all'elemento i del vettore dei Pcb */
        pcb_t* newPcbEl = &pcbFree_table[i];
        /* Aggiungo l'elemento alla lista pcbFree concatenando il puntatore al list_head dell'elemento e la sentinella della lista (pcbFree_h) */
	list_add(&(newPcbEl->p_next), &(pcbFree_h)); /* Aggiunge l'elemento in testa che rimane puntato da pcbFree_h che è la sentinella della lista*/
	}
}


/* -------------------- FUNZIONE 2 -------------------- */

void freePcb(pcb_t *p)
{
    /* Aggiungo l'elemento puntato da p alla lista pcbFree concatenando il puntatore al list_head dell'elemento e la sentinella (pcbFree_h) */
    list_add(&(p->p_next), &(pcbFree_h)); 
    /* Non c'è bisogno di reinizializzare *p poiché verrà inizializzato in fase di allocazione */
}


/* -------------------- FUNZIONE 3 -------------------- */

pcb_t* allocPcb()
{
   /* Se la lista pcbFree è vuota ritorna NULL */
   if(list_empty(&(pcbFree_h))){return NULL;}
   /* Altrimenti: */
   else{
   /* Salvo il puntatore del pcb da rimuovere*/
   pcb_t* P_pcb = container_of(pcbFree_h.next, pcb_t, p_next);
   /* Stacco l'elemento dalla lista */
   list_del(pcbFree_h.next);
   /* Inizializzo i campi, del pcb_t puntato da P_pcb, a NULL/0 */
   INIT_LIST_HEAD(&(P_pcb->p_next));
   INIT_LIST_HEAD(&(P_pcb->p_child));
   INIT_LIST_HEAD(&(P_pcb->p_sib));
   P_pcb->p_parent = NULL;
   INIT_STATE(&(P_pcb->p_s));
   P_pcb->p_semkey = NULL;
   P_pcb->priority = 0;
   /* Restituisco il puntatore all'elemento rimosso */
   return P_pcb;
   }
}


/* -------------------- FUNZIONE 4 -------------------- */

void mkEmptyProcQ(struct list_head *head)
{
    /* inizializzo i puntatori della sentinella */
    INIT_LIST_HEAD(head);
}


/* -------------------- FUNZIONE 5 -------------------- */

int emptyProcQ(struct list_head *head)
{ 
    return list_empty(head); /* restituisco TRUE se la lista puntata da head è vuota, FALSE altrimenti */
}


/* -------------------- FUNZIONE 6 -------------------- */

void insertProcQ(struct list_head* head, pcb_t* p)
{
	pcb_t *iterator; /* Variabile di tipo puntatore all'elemento pcb_t, consente di scorrere la lista */
/* Controllo se la lista puntata dalla sentinella head è vuota */
  if(emptyProcQ(head)) /* Se è vuota */
  {
	/* Aggiungo l'elemento p in testa alla lista, dopo la sentinella */
	list_add(&(p->p_next), head);
	return;
  }
    else /*Altrimenti*/
   {

	/* Scorro la lista dei processi puntata da head */
	list_for_each_entry(iterator, head, p_next){
	/* Confronto il campo priorità dell'elemento puntato da p con ogniuno di quelli presenti nella lista */
	/* Se l'elemento puntato da p ha priorità maggiore rispetto a quello puntato dall'iteratore */
		if (p->priority > iterator->priority){
	/* Allora aggiungo p in coda a tale elemento, il campo prev di p punterà all'iteratore, il campo next di p punterà all'elemento successivo all'iteratore, il quale campo next punterà a sua volta p */
			list_add_tail(&(p->p_next), &(iterator->p_next));
			return;
		}
	}
	/* Se la priorità di p non è maggiore di nessun elemento nella lista allora andrà aggiunto per ultimo, in coda alla lista */
	list_add_tail(&(p->p_next), head);
	return;
   }
}


/* -------------------- FUNZIONE 7 -------------------- */

pcb_t *headProcQ(struct list_head *head)
{
    /* Se la lista è vuota ritorno null */
    if(list_empty(head))
        return NULL;
    /* estraggo l'indirizzo del primo elemento della lista */
    struct list_head *first = list_next(head);
    /* estraggo l'indirizzo del contenitore di first */
    pcb_t *firstPcb = container_of(first, pcb_t, p_next);
    /* lo restituisco */
    return firstPcb;
}


/* -------------------- FUNZIONE 8 -------------------- */

pcb_t* removeProcQ(struct list_head *head)
{
     pcb_t *firstPcb = headProcQ(head); /* Ritorna NULL se la lista è vuota o il primo elemento della lista */
    if(firstPcb != NULL) /* Se la lista non è vuota */
    { list_del(&(firstPcb->p_next));} /* elimino l'elemento dalla lista*/
    /* Ritorno NULL o il puntatore all'elemento rimosso */
    return firstPcb;
}


/* -------------------- FUNZIONE 9 -------------------- */

pcb_t *outProcQ(struct list_head *head, pcb_t *p)
{
    /*  Scorro la lista dei pcb  */
    struct list_head* pos;
    list_for_each(pos, head)
    {
        /*  Estraggo il puntatore all'elemento corrente */
        pcb_t* curr = container_of(pos, pcb_t, p_next);
        /*  Se l'elemento corrente è uguale a quello da eliminare */
        if(p == curr)
        {
            list_del((&(p->p_next))); /* Lo elimino */
            return p;
        }
    }	
	return NULL; /* Altrimenti ritorno NULL se l'elemento richiesto non è presente */
}


/* -------------------- FUNZIONE 10 -------------------- */

int emptyChild(pcb_t *p) 
{
   return list_empty(&(p->p_child)); /* Restituisce true se la lista dei processi figli è vuota, false altrimenti */
}


/* -------------------- FUNZIONE 11 -------------------- */

void insertChild(pcb_t *prnt,pcb_t *p) 
{
    p->p_parent = prnt; /* p è figlio di prnt */
    /* aggiungo l'elemento in coda alla lista dei figli*/
    list_add_tail(&(p->p_sib), &(prnt->p_child));
}


/* -------------------- FUNZIONE 12 -------------------- */

pcb_t* removeChild(pcb_t *p)
{
	pcb_t* first_PcbChild = NULL; /* Variabile che conterrà il puntatore al primo figlio */
	/*Controllo se p ha figli.*/    
    if (!emptyChild(p)) 
    {
	/* estraggo l'indirizzo del primo concatenatore figlio */
        struct list_head* firstChild = list_next(&(p->p_child));
        /* estraggo l'indirizzo del contenitore del primo concatenatore */
        first_PcbChild = container_of(firstChild, pcb_t, p_sib); 
        /* elimino il puntatore al padre */
        first_PcbChild->p_parent = NULL;
        /* elimino il figlio dalla lista */
        list_del(firstChild);	
        		
    }
	return first_PcbChild; /* restituisco NULL o il puntatore al figlio rimosso */
}


/* -------------------- FUNZIONE 13 -------------------- */

pcb_t* outChild(pcb_t *p) 
{
    /*controllo se p ha un padre.Se non ha un padre restituisco NULL*/
    if ((&(p->p_parent))== NULL)
        return NULL;
        
        else 
        {
            /*elimino elemento dall'albero*/
            list_del (&(p->p_sib));
            p->p_parent = NULL;
            /*restituisco elemento rimosso*/
            return p;
        }
}













