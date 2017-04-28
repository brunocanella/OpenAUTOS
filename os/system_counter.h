#ifndef OS_SYSTEM_COUNTER_H
#define OS_SYSTEM_COUNTER_H

#include "types.h"

void InitializeSystemCounter();

uint8_t HasInterruptSystemCounter();

void TimeoutRoutineSystemCounter();

void ResetSystemCounter();

#endif//OS_SYSTEM_COUNTER_H