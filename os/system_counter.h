#ifndef OS_SYSTEM_COUNTER_H
#define OS_SYSTEM_COUNTER_H

#include "types.h"

/**
 * Initializes the internal system counter
 */
void InitializeSystemCounter();

/**
 * Detects if the system counter has triggered
 */
uint8_t HasInterruptSystemCounter();

/**
 * A callback registered to the system counter will be called by this rotine.
 */
void TimeoutRoutineSystemCounter();

/**
 * Resets the system counter to perform another countdown.
 */
void ResetSystemCounter();

/**
 * The type for the callback rotine for TimeoutRoutineSystemCounter.
 */
typedef void (*TimeoutCallbackSystemCounterType)();

/**
 * The callback rotine to be called by TimeoutRoutineSystemCounter
 */
extern TimeoutCallbackSystemCounterType g_callback_timeoutsystemcounter;

#endif//OS_SYSTEM_COUNTER_H