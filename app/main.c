// OpenAUTOS
#include <openautos.h>

const uint8_t TASKS_TOTAL_TYPES = 3;
const uint8_t TASKS_TOTAL = 5;

#define TASK_FOO 1
#define TASK_BAR 2
#define TASK_BAZ 3

void f_task_1() { 
	PORTBbits.RB0 = 0;
	ChainTask(TASK_BAR);
}

void f_task_2() { 
    PORTBbits.RB0 = !LATBbits.LATB0;

    while(1) { NOP(); }
	//ChainTask(TASK_FOO);
}
void f_task_3() { 
	NOP(); 
	TerminateTask();
}

void InitializeTasks() {
	////////////////////
	// Idle Task
	////////////////////
	g_idle->id = TASKID_IDLE;
	g_idle->priority = 0;
	g_idle->state = READY;
	ResetTaskContext( &(g_idle->context), IdleTask_Callback );
	g_idle->callback = IdleTask_Callback;
	g_idle->next_task_same_priority = g_idle;

	////////////////////
	// User Tasks
	////////////////////
	TaskDataRefType t1_1 = &g_tasks[0];
	t1_1->id = TASK_FOO;
	t1_1->priority = TASK_FOO;
	t1_1->state = SUSPENDED;
	ResetTaskContext( &t1_1->context, f_task_1 );
	t1_1->callback = f_task_1;

	t1_1->next_task_same_priority = t1_1;

	TaskDataRefType t2_1 = &g_tasks[1];
	t2_1->id = TASK_BAR;
	t2_1->priority = TASK_BAR;
	t2_1->state = READY;
	ResetTaskContext( &t2_1->context, f_task_2 );
	t2_1->callback = f_task_2;

	TaskDataRefType t2_2 = &g_tasks[2];
	t2_2->id = TASK_BAR;
	t2_2->priority = TASK_BAR;
	t2_2->state = READY;
	ResetTaskContext( &t2_2->context, f_task_2 );
	t2_2->callback = f_task_2;

	TaskDataRefType t2_3 = &g_tasks[3];
	t2_3->id = TASK_BAR;
	t2_3->priority = TASK_BAR;
	t2_3->state = SUSPENDED;
	ResetTaskContext( &t2_3->context, f_task_2 );
	t2_3->callback = f_task_2;

	t2_1->next_task_same_priority = t2_2;
	t2_2->next_task_same_priority = t2_3;
	t2_3->next_task_same_priority = t2_1;

	TaskDataRefType t3_1 = &g_tasks[4];
	t3_1->id = TASK_BAZ;
	t3_1->priority = TASK_BAZ;
	t3_1->state = SUSPENDED;
	ResetTaskContext( &t3_1->context, f_task_3 );
	t3_1->callback = f_task_3;

	t3_1->next_task_same_priority = t3_1;
	////////////////////
	// Set Active Task
	////////////////////
	g_active_task = g_idle;
}

void main(void) {
	asm("GLOBAL _f_task_1, _f_task_2, _f_task_3");

    TRISBbits.TRISB0 = OUTPUT;
    PORTBbits.RB0 = LOW;

    InitializeTasks();    

    StartOS( 0 );
    
    while( 1 ) {
    	for( uint16_t i = 0; i < 20000; i++ ) {
        	asm("nop");
    	}
    	//PORTBbits.RB0 = !LATBbits.LATB0;
    }
    
    return;
}

