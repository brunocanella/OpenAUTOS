#ifndef OS_SYSTEM_COUNTER_H
#define OS_SYSTEM_COUNTER_H

#include "types.h"

void InitializeSystemCounter();

uint8_t HasInterruptSystemCounter();

void TimeoutRoutineSystemCounter();

void ResetSystemCounter();

typedef void (*TimeoutCallbackSystemCounterType)();

extern TimeoutCallbackSystemCounterType g_callback_timeoutsystemcounter;

#endif//OS_SYSTEM_COUNTER_H