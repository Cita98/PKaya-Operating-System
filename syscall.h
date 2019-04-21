#include "types_rikaya.h"
#include "myConst.h"
#include "types.h"
#include "scheduler.h"
#include "p1.5test_rikaya_v0.c"

void syscall_handler();
void terminateProcess(struct list_head* head_rd);
