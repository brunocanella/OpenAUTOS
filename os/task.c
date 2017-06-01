#include "task.h"

#include <xc.h>

/**Global array holding all the tasks*/
TaskDataType g_tasks[TASKS_TOTAL+1]; //+1 for the idle task

TaskDataRefType g_idle = &g_tasks[TASKS_TOTAL]; // Idle Task goes in the last position

TaskDataRefType g_active_task = NULL;

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

void InitializeTaskData(
    TaskDataRefType Task,
    TaskType Id, 
    TaskPriorityType Priority,
    TaskStateType State,
    TaskCallbackType Callback
) {
    Task->id = Id;
    Task->priority = Priority;
    Task->priority_base = Priority;
    Task->state = State;
    Task->callback = Callback;    
    Task->next_task_same_priority = Task;
    ResetTaskContext( &Task->context, Callback );
    InitializeResourceDataList( &Task->resources );
}

void GroupTasksSamePriority() {
    for( uint8_t i = 0; i < TASKS_TOTAL-1; i++ ) {
        TaskDataRefType l_task = &g_tasks[i];
        TaskDataRefType l_first = l_task;
        TaskDataRefType l_last = l_task;
        if( l_task->next_task_same_priority != l_task ) { continue; }
        for( uint8_t j = i+1; j < TASKS_TOTAL; j++ ) {
            TaskDataRefType l_test = &g_tasks[j];
            if( l_task != l_test && l_task->priority_base == l_test->priority_base ) {
                l_task->next_task_same_priority = l_test;
                l_task = l_test;
                l_last = l_test;
            }
        }
        if( l_last != l_first ) {
            l_last->next_task_same_priority = l_first;
        }
    }
}
