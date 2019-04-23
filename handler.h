#ifndef HANDLER_H
#define HANDLER_H

#include "interrupt.h"
#include "syscall.h"
#include "scheduler.h"
#include "myConst.h"
#include "utilis.h"

void int_handler(); // Handler per gli interrupt

void syscall_handler(); // Handler per le systemcall


#endif
