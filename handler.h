#ifndef __HANDLERS
#define __HANDLERS

//alcuni header da creare

#include "scheduler.h"
#include "utils.h"
#include "kernelVariables.h"
#include "syscall.h"
#include "interrupt.h"
#include "asl.h"
#include "libumps.h" //per funzione getPRID

void syscall_handler();

void int_handler();


#endif
