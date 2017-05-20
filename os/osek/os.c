#include "os.h"

#include "../setup.h" // OpenAUTOS boot sequence
#include "tasks.h"

#include "interrupts.h" // OSEK Interrupts

AppModeType g_app_mode;

AppModeType GetActiveApplicationMode( void ) {
	return g_app_mode;
}

#include "../task.h"


static bank0 uint8_t stack_u;
static bank0 uint8_t stack_h;
static bank0 uint8_t stack_l;

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

    // Limpando a pilha
	while( uControllerStackValue() > 0 ) { POP(); }
	// Carregando o callback
	g_active_task->context.stack_top = 0;	
    PUSH();
    uint24_t l_callback = (uint24_t) g_active_task->callback;
    stack_u = l_callback >> 16;
    stack_h = l_callback >>  8;
    stack_l = l_callback >>  0;
    asm("NOP");
    asm("MOVF _stack_u,w");
    asm("MOVWF TOSU");
    asm("MOVF _stack_h,w");
    asm("MOVWF TOSH");
    asm("MOVF _stack_l,w");
    asm("MOVWF TOSL");

    EnableAllInterrupts();
}