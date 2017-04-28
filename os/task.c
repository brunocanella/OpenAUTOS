#include "task.h"

#include "debugger.h"

/**Global array holding all the tasks*/
TaskDataType g_tasks[TASKS_TOTAL+1]; //+1 for the idle task

TaskDataRefType g_idle = &g_tasks[TASKS_TOTAL]; // Idle Task goes in the last position

TaskDataRefType g_active_task = NULL;

void InitializeIdleTask() {
	g_idle->id = TASKID_IDLE;
	g_idle->priority = 0;
	g_idle->state = RUNNING; // Starts in Running Mode. Will be exchanged with another task after a schedule.

	ResetTaskContext( &(g_idle->context) );

	g_idle->callback = NULL; // TODO criar rotina de callback para idle (conforme uControlador)

	g_active_task = g_idle;
}


/**
 * Private helper method to retrieve the task based on the ID
 * 
 * @param TaskId Id of the task being searched for
 * @param TaskState If given a value different from 0, filters by the task state
 */
TaskDataRefType GetTaskRefById( TaskType TaskId, TaskStateType TaskState ) {
	for( int i = 0; i < TASKS_TOTAL; i++ ) {
		if( g_tasks[i].id == TaskId && ( !TaskState || g_tasks[i].state == TaskState ) ) {
			return &g_tasks[i];
		}
	}

	return NULL;
}

////////////////////////////////////////////////////////////////////////////////
//  OSEK Methods
////////////////////////////////////////////////////////////////////////////////

StatusType ActivateTask( TaskType TaskID ) {
	// Searches for the task with the given ID
	uint8_t l_task_id_found = FALSE;
	TaskDataRefType l_task_data_ref = NULL;
	for( int8_t i = 0; i < TASKS_TOTAL; i++ ) {
		if( g_tasks[i].id == TaskID ) {
			l_task_id_found = TRUE;
			if( g_tasks[i].state == SUSPENDED ) {
				l_task_data_ref = &g_tasks[i];
				break;
			}
		}
	}
	if( l_task_id_found == FALSE ) {
		LOGGER_ERROR( ("TaskId \"%d\" not found", TaskID) );
		return E_OS_ID;
	} else if ( l_task_data_ref == NULL ) {
		LOGGER_DEBUG( ("TaskId \"%d\" has no task suspended", TaskID) );
		return E_OS_LIMIT;
	}
	// Task was found, now activate it and reset the context

	l_task_data_ref->state = RUNNING;
	ResetTaskContext( &(l_task_data_ref->context) );

	// All systems are green. Mission is a go

	return E_OK;
}


StatusType TerminateTask( void ) { return E_OK; }
StatusType ChainTask( TaskType TaskID ) { return E_OK; }
StatusType GetTaskID( TaskRefType TaskID ) { return E_OK; }
StatusType GetTaskState( TaskType TaskID, TaskStateRefType State ) { return E_OK; }

