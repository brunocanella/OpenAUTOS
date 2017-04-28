#include "interrupts.h" // OSEK Interrupts

#include "../interrupts.h"

void EnableAllInterrupts( void ) {
	ENABLE_GLOBAL_INTERRUPTS();
}

void DisableAllInterrupts( void ) {
	DISABLE_GLOBAL_INTERRUPTS();
}