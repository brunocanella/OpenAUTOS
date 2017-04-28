#include "scheduler.h"

#include "../task.h"

StatusType Schedule( void ) {
    // Start with the IDLE task as the active highest priority that is READY
    TaskDataRefType l_highest = &g_tasks[0];
    // Loops through all tasks, finding the ones that are READY
    for( uint8_t i = 0; i < TASKS_TOTAL; i++ ) {
    	TaskDataRefType l_curr = &g_tasks[i+1];
        if( l_curr->state == READY ) {
        	if( l_curr->priority > l_highest->priority ) {
        		l_highest = l_curr;
        	}
        }
    }

    // TODO Keep doing the scheduler
    // if( l_highest->priority > g_active_task ) {
    //     
    // }

    return E_OK;
}