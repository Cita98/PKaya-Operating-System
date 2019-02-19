#include <pcb.h>

void initPcbs(void)
{
	HIDDEN pcb_t pcbFree_table[MAXPROC];
	int i; /* Counter */
    /* Inizializzazione della sentinella */
    INIT_LIST_HEAD(&(pcbFree_h));
    /* Inizializzazione della lista pcbFree */
    for (i = 0; i < MAXPROC; i++)
    {
        pcb_t* newPcbEl = &pcbFree_table[i];
        /* Infine congiungo opportunamente i concatenatori di elemento e sentinella/head */
	list_add(&(newPcbEl->p_next), &(pcbFree_h)); /*mette in testa alla lista pcbFree_h che è la sentinella*/
	}
}

void freePcb(pcb_t *p)
{
    /* Non c'è bisogno di reinizializzare *p poiché verrà inizializzato in fase di allocazione */
    list_add(&(p->p_next), &(pcbFree_h));
}

pcb_t* allocPcb()
{
   /* Se la lista pcbFree è vuota ritorna NULL */
   if (list_empty(&(pcbFree_h))) return NULL;

   /* Altrimenti: */
   /* Salvo il puntatore del pcb da allocare */
   pcb_t* allocPpcb = container_of(pcbFree_h.next, pcb_t, p_next);
   /* Stacco l'elemento dalla lista */
   list_del(pcbFree_h.next);
   /* Inizializzo i campi del pcb_t puntato da allocPpcb */
   INIT_LIST_HEAD(&(allocPpcb->p_next));
   INIT_LIST_HEAD(&(allocPpcb->p_child));
   INIT_LIST_HEAD(&(allocPpcb->p_sib));
   allocPpcb->p_parent = NULL;
   cleanState(&(allocPpcb->p_s));
   allocPpcb->priority = DEFAULT_PCB_PRIORITY;
   allocPpcb->p_semkey = -1; /* non è bloccato su alcun semaforo */
   /* Inizializzo il custom handler a NULL */
   int i;
   for(i=0;i<8;i++)
   {
		allocPpcb->custom_handlers[i] = NULL;
   }
   /* Inizializzo il tempo CPU a 0 */
   allocPpcb->time = 0;
   /* Il processo NON va terminato (ovviamente) */
   allocPpcb->wanted = 0;
   /* Ritorno il puntatore al pcb_t */
   return allocPpcb;
}

void mkEmptyProcQ(struct list_head *head)
{
    /* inizializzo i puntatori della sentinella */
    INIT_LIST_HEAD(head);
}

int emptyProcQ(struct list_head *head)
{ 
    return list_empty(head);
}

void insertProcQ(struct list_head* head, pcb_t* p)
{
	pcb_t *iterator;
	
	list_for_each_entry(iterator, head, p_next){
		if (p->priority > iterator->priority){
			list_add_tail(&(p->p_next), &(iterator->p_next));
			return;
		}
	}
	list_add_tail(&(p->p_next), head);
}

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

pcb_t* removeProcQ(struct list_head *head)
{
    /* Se la lista è vuota ritorno NULL */
    if (list_empty(head))
    	return NULL;
	/* estraggo l'indirizzo del primo elemento della lista */
    struct list_head* first = list_next(head);
    /* estraggo l'indirizzo del contenitore di first */
    pcb_t* firstPcb = container_of(first, pcb_t, p_next);
    /* elimino l'elemento */
    list_del(first);
    /* ritorno il puntatore all'elemento rimosso */
    return firstPcb;
}

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
            list_del((&(p->p_next)));
            return p;
        }
    }
    /* ritorno null se l'elemento richiesto non è presente */
    return NULL;
}

int emptyChild(pcb_t *p) 
{
   return list_empty(&(p->p_child));
}

void insertChild(pcb_t *prnt,pcb_t *p) 
{
    p->p_parent = prnt;
    /* aggiungo l'elemento in coda alla lista dei figli*/
    list_add_tail(&(p->p_sib), &(prnt->p_child));
}

pcb_t* removeChild(pcb_t *p)
{
	/*Controllo se p non ha figli.*/    
    if (list_empty(&(p->p_child)))
    {
        return NULL;
	} 
	else 
	{
		/* estraggo l'indirizzo del primo concatenatore figlio */
        struct list_head* firstChild = list_next(&(p->p_child));
        /* estraggo l'indirizzo del contenitore del primo concatenatore */
        pcb_t* firstPcb = container_of(firstChild, pcb_t, p_sib); 
        /* elimino il puntatore al padre */
        firstPcb->p_parent = NULL;
        /* elimino il figlio dalla lista */
        list_del(firstChild);	
        /* restituisco il puntatore al figlio rimosso */
		return firstPcb;
	}
}

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
            /*restituisco elemento da rimuovere*/
            return p;
        }
}













