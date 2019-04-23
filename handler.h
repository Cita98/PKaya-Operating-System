#ifndef HANDLER_H
#define HANDLER_H

#include "interrupt.h"
#include "syscall.h"
#include "scheduler.h"
#include "myConst.h"
#include "utilis.h"

void int_handler();

void syscall_handler();


#endif
