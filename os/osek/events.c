#include "events.h"

#include "../debugger.h"        // LOGGER_ERROR, LOGGER_DEBUG
#include "../task.h"            // TaskDataRefType
#include "../system_counter.h"  // StopScheduler, ResumeScheduler
#include "../interrupts.h"         // IS_ON_INTERRUPT

#include <xc.h>

static TaskDataRefType l_task_data_ref;
StatusType SetEvent( TaskType TaskID, EventMaskType Mask ) {
    StopScheduler();
    // Searches for the task with the given ID
    uint8_t l_task_id_found = FALSE;
    l_task_data_ref = NULL;
    for( uint8_t i = 0; i < TASKS_TOTAL; i++ ) {
        if( g_tasks[i].id == TaskID ) {
            l_task_id_found = TRUE;
            if( g_tasks[i].state == WAITING ) {
                l_task_data_ref = &g_tasks[i];
                break;
            }
        }
    }
    if( l_task_id_found == FALSE ) {
        LOGGER_ERROR( ("TaskId \"%d\" not found\n", TaskID) );
        ReturnResumeScheduler(E_OS_ID);
    } else 
//    if( !l_task_data_ref->extended ) { 
//        return E_OS_ACCESS; 
//    } else
    if ( l_task_data_ref == NULL ) {
        LOGGER_DEBUG( ("Events can not be set as the referenced task is in the suspended state,\n", TaskID) );
        ReturnResumeScheduler(E_OS_STATE);
    }
    
    // Setting the event flag
    l_task_data_ref->events.flag |= Mask;
    // if the task is 
    if( ( l_task_data_ref->events.flag & l_task_data_ref->events.wait ) > 0 ) {
        l_task_data_ref->state = READY;        
        if( !IS_ON_INTERRUPT() ) {
            //TODO: Resume Timer
            ReturnResumeScheduler(Schedule());
        }
    }
    // TODO: Resume Timer
    ReturnResumeScheduler(E_OK);
}

StatusType ClearEvent( EventMaskType Mask ) {
    StopScheduler();
    if( g_active_task == NULL ) {
        LOGGER_ERROR( ("ClearEvent ERROR: Active Task is NULL.\n") );
        OS_RESET();
    }
//    if( !g_active_task->extended ) { 
//        return E_OS_ACCESS; 
//    } else
    if ( IS_ON_INTERRUPT() ) {
        LOGGER_DEBUG( ("ClearEvent WARNING: Call at interrupt level.\n") );
        ReturnResumeScheduler(E_OS_CALLEVEL);
    }
    
    g_active_task->events.flag &= ~Mask;
    
    ReturnResumeScheduler(E_OK);
}

StatusType GetEvent( TaskType TaskID, EventMaskRefType Event ) {
    StopScheduler();
    l_task_data_ref = NULL;
    for( uint8_t i = 0; i < TASKS_TOTAL; i++ ) {
        if( g_tasks[i].id == TaskID ) {
            l_task_data_ref = &g_tasks[i];
            break;            
        }
    }
    if( l_task_data_ref == NULL ) {
        LOGGER_ERROR( ("TaskId \"%d\" not found\n", TaskID) );
        ReturnResumeScheduler(E_OS_ID);
    } else
//    if( !g_active_task->extended ) { 
//        return E_OS_ACCESS; 
//    } else
    if( l_task_data_ref->state == SUSPENDED ) {
        LOGGER_DEBUG( ("GetEvent WARNING: Referenced task TaskID is in the suspended state.\n") );
        ReturnResumeScheduler(E_OS_STATE);
    }
    
    if( Event != NULL ) {
        (*Event) = l_task_data_ref->events.flag;
    }
    
    ReturnResumeScheduler(E_OK);
}

/**
 * The state of the calling task is set to waiting, unless at least one of the events specified in <Mask> has already been set.
 *
 * @remark This call enforces rescheduling, if the wait condition occurs. If rescheduling takes place, the internal resource of the task is released while the task is in the waiting state.
 * @remark This service shall only be called from the extended task owning the event.
 *
 * @param[in] Mask Mask of the events waited for.
 * 
 * @return [Standard] No error, E_OK.
 * @return [Extended] Calling task is not an extended task, E_OS_ACCESS.
 * @return [Extended] Calling task occupies resources, E_OS_RESOURCE.
 * @return [Extended] Call at interrupt level, E_OS_CALLEVEL.
 */
StatusType WaitEvent( EventMaskType Mask ) {
    StopScheduler();
    if( g_active_task == NULL ) {
        LOGGER_ERROR( ("WaitEvent ERROR: Active Task is NULL.\n") );
        OS_RESET();
    }
//    if( !g_active_task->extended ) { 
//        return E_OS_ACCESS; 
//    } else
    if( g_active_task->priority != g_active_task->priority_base ) {
        LOGGER_DEBUG( ("WaitEvent WARNING: Calling task occupies resources,\n") );
        ReturnResumeScheduler(E_OS_RESOURCE);
    } else
    if( IS_ON_INTERRUPT() ) {
        LOGGER_DEBUG( ("WaitEvent WARNING: Call at interrupt level.\n") );
        ReturnResumeScheduler(E_OS_CALLEVEL);
    }
    
    g_active_task->events.wait = Mask;
    
    // If no event in wait is set, then this task goes into WAITING state a event is set.
    if( g_active_task->events.wait & g_active_task->events.flag ) {
        ReturnResumeScheduler(E_OK);
    }
    
    g_active_task->state = WAITING;
    ReturnResumeScheduler(Schedule());
}