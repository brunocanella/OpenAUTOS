// OpenAUTOS
#include <openautos.h>

const uint8_t TASKS_TOTAL_TYPES = 3;
const uint8_t TASKS_TOTAL = 5;

#define TASK_FOO 1
#define TASK_BAR 2
#define TASK_BAZ 3

void InitializeTaskMetadata() {
	TaskMetaDataRefType mdt_1 = &g_task_metadata[0];
	mdt_1->id = TASK_FOO;
	mdt_1->activations = 1;
	mdt_1->current_active = 1;

	TaskMetaDataRefType mdt_2 = &g_task_metadata[1];
	mdt_2->id = TASK_BAR;
	mdt_2->activations = 3;
	mdt_2->current_active = 1;

	TaskMetaDataRefType mdt_3 = &g_task_metadata[2];
	mdt_3->id = TASK_BAZ;
	mdt_3->activations = 1;
	mdt_3->current_active = 1;
}



void f_foo() { NOP(); }
void f_bar() { NOP(); }
void f_baz() { NOP(); }

void InitializeTasks() {
	InitializeIdleTask();	

	TaskDataRefType t1_1 = &g_tasks[1];
	t1_1->id = TASK_FOO;
	t1_1->priority = TASK_FOO;
	t1_1->state = SUSPENDED;
	ResetTaskContext( &t1_1->context );
	t1_1->callback = f_foo;

	TaskDataRefType t2_1 = &g_tasks[2];
	t2_1->id = TASK_BAR;
	t2_1->priority = TASK_BAR;
	t2_1->state = SUSPENDED;
	ResetTaskContext( &t2_1->context );
	t2_1->callback = f_bar;

	TaskDataRefType t2_2 = &g_tasks[3];
	t2_2->id = TASK_BAR;
	t2_2->priority = TASK_BAR;
	t2_2->state = SUSPENDED;
	ResetTaskContext( &t2_2->context );
	t2_2->callback = f_bar;

	TaskDataRefType t2_3 = &g_tasks[4];
	t2_3->id = TASK_BAR;
	t2_3->priority = TASK_BAR;
	t2_3->state = SUSPENDED;
	ResetTaskContext( &t2_3->context );
	t2_3->callback = f_bar;

	TaskDataRefType t3_1 = &g_tasks[5];
	t3_1->id = TASK_BAZ;
	t3_1->priority = TASK_BAZ;
	t3_1->state = SUSPENDED;
	ResetTaskContext( &t3_1->context );
	t3_1->callback = f_baz;
}

void main(void) {
    TRISBbits.TRISB0 = OUTPUT;
    PORTBbits.RB0 = LOW;

    InitializeTasks();
    InitializeTaskMetadata();

    StartOS( 0 );
    
    while( 1 ) {
    	for( uint16_t i = 0; i < 20000; i++ ) {
        	asm("nop");
    	}
    	//PORTBbits.RB0 = !LATBbits.LATB0;
    }
    
    return;
}
