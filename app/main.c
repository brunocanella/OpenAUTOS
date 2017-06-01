// OpenAUTOS
#include <openautos.h>

const uint8_t TASKS_TOTAL_TYPES = 3;
const uint8_t TASKS_TOTAL = 5;

#define TASK_FOO 1
#define TASK_BAR 2
#define TASK_BAZ 4

#define RES_A 1
#define RES_B 2
#define RES_C 3

void f_task_1() { 	
    // Allocate Resource
    GetResource( RES_A );    
    // Initiate task with priority 2
    ActivateTask( TASK_BAR );
    PORTBbits.RB0 = 0;
    ReleaseResource( RES_A );
	while(TRUE) { NOP(); }
}

void f_task_2() {    
    PORTBbits.RB0 = 1;
    ActivateTask( TASK_BAZ );
    GetResource( RES_C );
    ActivateTask( TASK_BAZ );
    ReleaseResource( RES_C );
    ChainTask( TASK_BAZ );
}
void f_task_3() { 
    PORTBbits.RB1 = !LATBbits.LATB1;
	TerminateTask();
}

void IdleTask_Callback() {
	while( TRUE ) {
		NOP();
	}
}

void InitializeTasks() {
	// Idle Tasks
    InitializeTaskData( g_idle, TASK_ID_IDLE, 0, READY, IdleTask_Callback );
	// User Tasks
    InitializeTaskData( &g_tasks[0], TASK_FOO, TASK_FOO, READY, f_task_1 );
    InitializeTaskData( &g_tasks[1], TASK_BAR, TASK_BAR, SUSPENDED, f_task_2 );
    InitializeTaskData( &g_tasks[2], TASK_BAR, TASK_BAR, SUSPENDED, f_task_2 );
    InitializeTaskData( &g_tasks[3], TASK_BAR, TASK_BAR, SUSPENDED, f_task_2 );
    InitializeTaskData( &g_tasks[4], TASK_BAZ, TASK_BAZ, SUSPENDED, f_task_3 );
    // Group tasks with same priority
    GroupTasksSamePriority();
}

ResourceDataType g_res[3];
void InititializeResources() {
    InitializeResourceDataList( &g_resources );
    AddResourceDataToResources( &g_res[0], RES_A, 3 );
    AddResourceDataToResources( &g_res[1], RES_B, 3 );
    AddResourceDataToResources( &g_res[2], RES_C, 5 );
}

void main(void) {
	asm("GLOBAL _IdleTask_Callback, _f_task_1, _f_task_2, _f_task_3");

    TRISBbits.TRISB0 = OUTPUT;
    PORTBbits.RB0 = LOW;
    TRISBbits.TRISB1 = OUTPUT;
    PORTBbits.RB1 = LOW;
   
    InitializeTasks();
    InititializeResources();

    StartOS( 0 );
    
    while( 1 ) {
    	for( uint16_t i = 0; i < 20000; i++ ) {
        	asm("nop");
    	}
    	//PORTBbits.RB0 = !LATBbits.LATB0;
    }
    
    return;
}

