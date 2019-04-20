#include "listx.h"
#include "myConst.h"
#include "pcb.h"

void scheduler(struct list_head* head_rq);
void context_switch(struct list_head* head_rq);
void aging(struct list_head* head_rq);



