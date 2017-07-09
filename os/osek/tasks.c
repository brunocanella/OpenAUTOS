#include "tasks.h"

#include "../debugger.h"
#include "../task.h"
#include "../system_counter.h"
#include "../interrupts.h"
#include "interrupts.h"

static uint8_t _at_main_id_found;
StatusType ActivateTask_Main( TaskType TaskID ) {
    // Searches for the task with the given ID
    _at_main_id_found = FALSE;
    TaskDataRefType l_task_data_ref = NULL;
    for( uint8_t i = 0; i < TASKS_TOTAL; i++ ) {
        if( g_tasks[i].id == TaskID ) {
            _at_main_id_found = TRUE;
            if( g_tasks[i].state == SUSPENDED ) {
                l_task_data_ref = &g_tasks[i];
                break;
            }
        }
    }
    if( _at_main_id_found == FALSE ) {
        LOGGER_ERROR( ("TaskId \"%d\" not found\n", TaskID) );
        return E_OS_ID;
    } else if ( l_task_data_ref == NULL ) {
        LOGGER_DEBUG( ("Maximun Activations for TaskId \"%d\" has been reached\n", TaskID) );
        return E_OS_LIMIT;
    }
    // Task was found, now activate it and reset the context
    
    ResetTaskContext( &(l_task_data_ref->context), l_task_data_ref->callback );
    l_task_data_ref->state = READY;

    return E_OK;
}

static StatusType l_status_activatetask;
StatusType ActivateTask( TaskType TaskID ) {    
    StopScheduler();
    l_status_activatetask = ActivateTask_Main( TaskID );    
    if( l_status_activatetask != E_OK ) {        
        ReturnResumeScheduler(l_status_activatetask);
    }
    // Finally, calls the scheduler to see if the new task will take over
    StatusType l_status = E_OK;
    l_status = Schedule();
    ReturnResumeScheduler(l_status);
}

StatusType TerminateTask_Main( void ) {
    // This service causes the termination of the calling task. 
    // The calling task is transferred from the running state into the suspended state.
    if( g_active_task == NULL ) {
        LOGGER_ERROR( ("TerminateTask ERROR: Active Task is NULL\n") );
        OS_RESET();
    } else if( g_active_task->state != RUNNING ) {
        LOGGER_DEBUG( ("TerminateTask WARNING: Active Task is not in the RUNNING state\n") );
    }
    g_active_task->state = SUSPENDED;

    // TODO: Release Internal Resources
    // TODO: Return E_OS_RESOURCE if Resource still occupied
    // TODO: Return E_OS_CALLEVEL if called at interrupt level.
    return E_OK;
}

static StatusType l_status_terminatetask;
StatusType TerminateTask( void ) {
    StopScheduler();
    l_status_terminatetask = TerminateTask_Main();    
    if( l_status_terminatetask != E_OK ) {        
        ReturnResumeScheduler(l_status_terminatetask);
    }

    StatusType l_status = E_OK;
    l_status = Schedule();
    ReturnResumeScheduler(l_status);
}

static StatusType l_status_chaintask;
StatusType ChainTask( TaskType TaskID ) {
    StopScheduler();
    l_status_chaintask = TerminateTask_Main();
    if( l_status_chaintask != E_OK ) {
        ReturnResumeScheduler(l_status_chaintask);
    }
    // Does the activation part
    l_status_chaintask = ActivateTask_Main( TaskID );
    if( l_status_chaintask != E_OK ) {
        ReturnResumeScheduler(l_status_chaintask);
    }

    l_status_chaintask = Schedule();
    ReturnResumeScheduler(l_status_chaintask);

    // @remark If the succeeding task is identical with the current task, this does not result in multiple requests. 
    // The task is not transferred to the suspended state, but will immediately become ready again.
    
    // @remark An internal resource assigned to the calling task is automatically released, 
    // even if the succeeding task is identical with the current task. 
    // Other resources occupied by the calling shall have been released before ChainTask is called. 
    // If a resource is still occupied in standard status the behaviour is undefined.
    
    // @remark If called successfully, ChainTask does not return to the call level and the status can not be evaluated.
    
    // @remark In case of error the service returns to the calling task and provides 
    // a status which can then be evaluated in the application.
    
    // @remark If the service ChainTask is called successfully, this enforces a rescheduling.
    
    // @remark Ending a task function without call to TerminateTask or ChainTask is strictly 
    // forbidden and may leave the system in an undefined state.
    
    // @remark If E_OS_LIMIT is returned the activation is ignored. 
    // When an extended task is transferred from suspended state into ready state all its events are cleared.
}

StatusType GetTaskID( TaskRefType TaskID ) {
    if( g_active_task == NULL ) {
        LOGGER_ERROR( ("Active task cannot be NULL. NEVER!\n") );
        OS_RESET();
    }
    (*TaskID) = g_active_task->id;

    return E_OK;
}

StatusType GetTaskState( TaskType TaskID, TaskStateRefType State ) {
    StopScheduler();
    for( uint8_t i = 0; i < TASKS_TOTAL; i++ ) {
        if( g_tasks[i].id == TaskID ) {
            // No error. Return State and E_OK.
            (*State) = g_tasks[i].state;
            ReturnResumeScheduler(E_OS_ID);
        }
    }
    ReturnResumeScheduler(E_OS_ID); 
}

static TaskDataRefType l_highest;
static TaskDataRefType l_curr;
static uint8_t schedule_gethigh;
TaskDataRefType Schedule_GetHighestReadyTask() {
    // Start with the IDLE task as the active highest priority that is (at least) READY.
    l_highest = g_idle;
    // Loops through all tasks, finding the one that is READY (or RUNNING) and that has the HIGHEST priority.
    for( schedule_gethigh = 0; schedule_gethigh < TASKS_TOTAL; schedule_gethigh++ ) {
        l_curr = &g_tasks[schedule_gethigh];
        if( ( l_curr->state == READY ) && l_curr->priority > l_highest->priority ) {
            l_highest = l_curr;            
        }
    }
    // Return the values found
    return l_highest;
}

static TaskContextRefType l_context;
static TaskDataRefType l_highest_task;
StatusType Schedule( void ) {
    StopScheduler();
    // [Extended] Call at interrupt level, E_OS_CALLEVEL
    if( IS_ON_INTERRUPT() ) {
        ReturnResumeScheduler(E_OS_CALLEVEL);
    }
    // Critical Test
    if( g_active_task == NULL ) {
        LOGGER_ERROR( ("Active task cannot be NULL. NEVER!\n") );
        OS_RESET();
    }
    // TODO: Implement resource allocations
    // if( HasResourceAllocated( g_active_task ) ) {
    //     return E_OS_RESOURCE;
    // }   
    
    // Get the highest READY task. In the worst case, it will be the idle task.
    l_highest_task = Schedule_GetHighestReadyTask();
    // If this task has a higger priority than the active one, then a context switch is on its way.
    if( (g_active_task->state != RUNNING) || (l_highest_task->priority > g_active_task->priority) ) {        
        l_context = &(g_active_task->context);        
        SaveTaskContext( l_context );
        // If it is, we change the current active task for this one.
        if( g_active_task->state == RUNNING ) {
            g_active_task->state = READY;    
        }
        l_highest_task->state = RUNNING;
        g_active_task = l_highest_task;
        // Since we have our new task, now we load its context.
        l_context = &(g_active_task->context);
#if defined(PLATFORM) &&  PLATFORM == PIC18F25K80
        LoadTaskContext( l_context,"Schedule");
#else
#error Platform not defined!
#endif        
    }
    // No error, E_OK.
    ReturnResumeScheduler(E_OK); // In theory, this return value is useless, since the method will return to another point in the stack.
}