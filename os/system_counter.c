#include "system_counter.h"

#if defined(PLATFORM) &&  PLATFORM == PIC18F25K80
#include "platform/pic18f25k80/system_counter.h"
#else
#error Platform not declared
#endif

#include "constants.h"

TimeoutCallbackSystemCounterType g_callback_timeoutsystemcounter;

void InitializeSystemCounter() {
	PlatformInitializeSystemCounter();
	PlatformResetSystemCounter();
	g_callback_timeoutsystemcounter = ResetSystemCounter;
}

uint8_t HasInterruptSystemCounter() {
	return PlatformHasInterruptSystemCounter();
}

void TimeoutRoutineSystemCounter() {
	if( g_callback_timeoutsystemcounter ) {
		g_callback_timeoutsystemcounter();
	}
}

void ResetSystemCounter() {
	PlatformResetSystemCounter();
}