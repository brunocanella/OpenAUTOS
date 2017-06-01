#include "os.h"

#include "../setup.h" // OpenAUTOS boot sequence
#include "tasks.h"

#include "interrupts.h" // OSEK Interrupts

AppModeType g_app_mode;

AppModeType GetActiveApplicationMode( void ) {
	return g_app_mode;
}

#include "../task.h"

void StartOS( AppModeType Mode ) {
	//TODO Treatment for AppMode
	
	// Initiliaze stuff for the platform in which OpenAUTOS is running
	Setup();

	// TODO Call User Hookup Routine

	// Start with the IDLE task as the active highest priority that is (at least) READY.
    g_active_task = g_idle;
    // Loops through all tasks, finding the one that is READY (or RUNNING) and that has the HIGHEST priority.
    for( uint8_t i = 0; i < TASKS_TOTAL; i++ ) {
        TaskDataRefType l_curr = &g_tasks[i];
        if( ( l_curr->state == READY ) && l_curr->priority > g_active_task->priority ) {
            g_active_task = l_curr;
        }
    }
    g_active_task->state = RUNNING;

    // Limpando a pilha
	while( uControllerStackValue() > 0 ) { POP(); }
	// Carregando o callback
	g_active_task->context.stack_top = 0;	
    PUSH();
    uint32_t l_callback = (uint32_t) g_active_task->callback;
    volatile uint8_t l_tos;    
    l_tos = l_callback >> 16;
    asm("BANKSEL(StartOS@l_tos)");
    asm("MOVF ((StartOS@l_tos) and 0FFh),w");
    asm("MOVWF TOSU");
    l_tos = l_callback >>  8;
    asm("BANKSEL(StartOS@l_tos)");
    asm("MOVF ((StartOS@l_tos) and 0FFh),w");
    asm("MOVWF TOSH");
    l_tos = l_callback >>  0;    
    asm("BANKSEL(StartOS@l_tos)");
    asm("MOVF ((StartOS@l_tos) and 0FFh),w");
    asm("MOVWF TOSL");

    EnableAllInterrupts();
}