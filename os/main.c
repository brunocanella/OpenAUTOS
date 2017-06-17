#include <openautos.h>

const uint8_t TASKS_TOTAL = 4;

const TaskType task_green = 1;
TASK(task_green);
const TaskType task_yellow = 2;
TASK(task_yellow);
const TaskType task_red = 3;
TASK(task_red);
const TaskType task_init = 4;
TASK(task_init);

void TASK_FUNC_IDLE() {
	while( TRUE ) { NOP(); }
}

void InitializeTasks() {
	InitializeTaskData( g_idle, TASK_ID_IDLE, 0, READY, TASK_FUNC_IDLE );
	InitializeTaskData( &g_tasks[0], task_green, 1, SUSPENDED, TASK_FUNC_task_green );
	InitializeTaskData( &g_tasks[1], task_yellow, 2, SUSPENDED, TASK_FUNC_task_yellow );
	InitializeTaskData( &g_tasks[2], task_red, 3, SUSPENDED, TASK_FUNC_task_red );
	InitializeTaskData( &g_tasks[3], task_init, 254, READY, TASK_FUNC_task_init );
	GroupTasksSamePriority();
}

void InititializeResources() {
}

asm("GLOBAL _TASK_FUNC_IDLE, _TASK_FUNC_task_green, _TASK_FUNC_task_yellow, _TASK_FUNC_task_red, _TASK_FUNC_task_init" );
#define LED_GREEN PORTBbits.RB0
#define LED_YELLOW PORTBbits.RB1
#define LED_RED PORTBbits.RB2
#define LED_RED_READ LATBbits.LATB2

TASK( task_init ) {
    TRISBbits.TRISB0 = OUTPUT;
    TRISBbits.TRISB1 = OUTPUT;
    TRISBbits.TRISB2 = OUTPUT;

    LED_GREEN = LOW;
    LED_YELLOW = LOW;
    LED_RED = LOW;
    ChainTask( task_green );
}

TASK( task_green ) {
	while( TRUE ) {
		LED_GREEN = HIGH;
		ActivateTask( task_yellow );
		LED_GREEN = LOW;
		ActivateTask( task_yellow );		
	}
}

TASK( task_yellow ) {
	LED_YELLOW = HIGH;
	ActivateTask( task_red );
	LED_YELLOW = LOW;
	ActivateTask( task_red );
	TerminateTask();
}

TASK( task_red ) {
	LED_RED = !LED_RED_READ;
	TerminateTask();
}

void main(void) {
	InitializeTasks();
	InititializeResources();

	StartOS( 0 );

	while( 1 ) { NOP(); }

	return;
}
