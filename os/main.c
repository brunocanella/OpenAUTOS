#include <openautos.h>

const uint8_t TASKS_TOTAL = 5;

const TaskType task_rb0 = 1;
TASK(task_rb0);
const TaskType task_rb1 = 2;
TASK(task_rb1);
const TaskType task_rb2 = 3;
TASK(task_rb2);
const TaskType task_start = 4;
TASK(task_start);
const TaskType task_init = 5;
TASK(task_init);

void TASK_FUNC_IDLE() {
	while( TRUE ) { Schedule(); }
}

void InitializeTasks() {
	InitializeTaskData( g_idle, TASK_ID_IDLE, 0, READY, TASK_FUNC_IDLE );
	InitializeTaskData( &g_tasks[0], task_rb0, 2, SUSPENDED, TASK_FUNC_task_rb0 );
	InitializeTaskData( &g_tasks[1], task_rb1, 2, SUSPENDED, TASK_FUNC_task_rb1 );
	InitializeTaskData( &g_tasks[2], task_rb2, 2, SUSPENDED, TASK_FUNC_task_rb2 );
	InitializeTaskData( &g_tasks[3], task_start, 3, SUSPENDED, TASK_FUNC_task_start );
	InitializeTaskData( &g_tasks[4], task_init, 1, READY, TASK_FUNC_task_init );
	GroupTasksSamePriority();
}

void InititializeResources() {
}

asm("GLOBAL _TASK_FUNC_IDLE, _TASK_FUNC_task_rb0, _TASK_FUNC_task_rb1, _TASK_FUNC_task_rb2, _TASK_FUNC_task_start, _TASK_FUNC_task_init" );
#include <stdint.h>

#define _XTAL_FREQ 64000000

void delay_s( uint8_t s ) {
	while( s > 0 ) {
		s--;
		for( uint8_t i = 0; i < 100; i++ ) {
			__delay_ms(10);
		}
	}
}

TASK( task_init ) {
	TRISB = 0x00; // Output Lower Bits
	LATB = 0x00;

	while( TRUE ) {
		ActivateTask( task_start );		
	}
}

TASK( task_start ) {		
	ActivateTask( task_rb0 );
	ActivateTask( task_rb1 );
	ActivateTask( task_rb2 );	
	LATB = 0;
	__delay_ms(10);
	TerminateTask();
}

TASK( task_rb0 ) {
	LATBbits.LATB0 = 1;
	__delay_ms(10);
	TerminateTask();
}

TASK( task_rb1 ) {
	LATBbits.LATB1 = 1;
	__delay_ms(10);
	TerminateTask();
}

TASK( task_rb2 ) {
	LATBbits.LATB2 = 1;
	__delay_ms(10);
	TerminateTask();
}
void main(void) {
	InitializeTasks();
	InititializeResources();

	StartOS( 0 );

	while( 1 ) { NOP(); }

	return;
}
