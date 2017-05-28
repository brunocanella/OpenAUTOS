#include "task.h"

#include <xc.h>

/**Global array holding all the tasks*/
TaskDataType g_tasks[TASKS_TOTAL+1]; //+1 for the idle task

TaskDataRefType g_idle = &g_tasks[TASKS_TOTAL]; // Idle Task goes in the last position

TaskDataRefType g_active_task = NULL;

void IdleTask_Callback() {
	while( TRUE ) {
		NOP();
	}
}

void InitializeIdleTask() {
	g_idle->id = TASKID_IDLE;
	g_idle->priority = 0;
	g_idle->state = READY;
	ResetTaskContext( &(g_idle->context), IdleTask_Callback );
	g_idle->callback = IdleTask_Callback;
	g_idle->next_task_same_priority = g_idle;
}
asm("GLOBAL _InitializeIdleTask, _IdleTask_Callback");

/**
 * Private helper method to retrieve the task based on the ID
 * 
 * @param TaskId Id of the task being searched for
 * @param TaskState If given a value different from 0, filters by the task state
 */
TaskDataRefType GetTaskRefById( TaskType TaskId, TaskStateType TaskState ) {
	for( uint8_t i = 0; i < TASKS_TOTAL; i++ ) {
		if( g_tasks[i].id == TaskId && ( !TaskState || g_tasks[i].state == TaskState ) ) {
			return &g_tasks[i];
		}
	}

	return NULL;
}

