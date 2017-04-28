#ifndef OS_ISR_H
#define OS_ISR_H

#if defined(PLATFORM) &&  PLATFORM == PIC18F25K80
#define ISR() void interrupt isr_os(void)
#else
#error Platform not declared
#endif

#include "system_counter.h"

ISR() {
	//CONTEXT_SAVE
	
	if( HasInterruptSystemCounter() ) {
		TimeoutRoutineSystemCounter();
		ResetSystemCounter();
	}

	//CONTEXT_LOAD
}

#endif//OS_ISR_H