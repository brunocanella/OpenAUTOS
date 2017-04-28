#include "system_counter.h"

#if defined(PLATFORM) &&  PLATFORM == PIC18F25K80
#include "platform/pic18f25k80/system_counter.h"
#else
#error Platform not declared
#endif

void InitializeSystemCounter() {
	PlatformInitializeSystemCounter();
	PlatformResetSystemCounter();	
}

uint8_t HasInterruptSystemCounter() {
	return PlatformHasInterruptSystemCounter();
}

// TODO Arrumar essa parada aqui
#include <xc.h>
void TimeoutRoutineSystemCounter() {
	PORTBbits.RB0 = !LATBbits.LATB0;
}

void ResetSystemCounter() {
	PlatformResetSystemCounter();
}