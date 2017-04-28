#include "os.h"

#include "../setup.h" // OpenAUTOS boot sequence

#include "interrupts.h" // OSEK Interrupts

AppModeType g_app_mode;

AppModeType GetActiveApplicationMode( void ) {
	return g_app_mode;
}

void StartOS( AppModeType Mode ) {
	//TODO Treatment for AppMode
	
	// Initiliaze stuff for the platform in which OpenAUTOS is running
	Setup();

	// TODO Call User Hookup Routine

	EnableAllInterrupts();
}