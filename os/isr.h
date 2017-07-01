#ifndef OS_ISR_H
#define OS_ISR_H

#if defined(PLATFORM) &&  PLATFORM == PIC18F25K80
#define ISR() void interrupt isr_os(void)
#define ISR_ENTER() do{ _wreg = WREG; _bsr = BSR; _status = STATUS; }while(0)
#define ISR_LEAVE() do{ STATUS = _status; BSR = _bsr; WREG = _wreg; }while(0)
#else
#error Platform not declared
#endif

// Timeout
#include "system_counter.h"
// Task Types
#include "task.h"
// Save/Load Context
#include "task_context.h"

ISR() {
    ISR_ENTER();
	if( HasInterruptSystemCounter() ) {		
		//////////////////////////////////
		// START => CONTEXT_SWITCH_TIMEOUT
		// In this case, we need to check if this task has other tasks with the same priority.
        TaskDataRefType l_test_task = g_active_task->next_task_same_priority;
        // Now, we loop through these tasks until we return to the original active task, 
        // or until we find a diferent task in the READY state.
        while( l_test_task != g_active_task ) {
            // If there is a next task with the same priority, check to see if it is in the READY state
            if( l_test_task->state == READY ) {
            	// A context switch will happen. First thing is to save the context of the active task.
            	TaskContextRefType l_context = &(g_active_task->context);
            	SaveTaskContext( l_context );
                // If it is, we change the current active task for this one.
                // TODO: Free Resources for Active Task? (Check on Manual)
                g_active_task->state = READY;
                //
                l_test_task->state = RUNNING;
                //
                g_active_task = l_test_task;
                // Since we have our new task, now we load its context.
                l_context = &(g_active_task->context);
#if defined(PLATFORM) &&  PLATFORM == PIC18F25K80
                LoadTaskContext( l_context,"isr_os");
#else
#error Platform not defined!
#endif            	
                break;
            // Else, we just keep looping through the next task with the same priority.
            } else {
                l_test_task = l_test_task->next_task_same_priority;
            }
        }
		// END => CONTEXT_SWITCH_TIMEOUT
		//////////////////////////////////
		TimeoutRoutineSystemCounter();
		ResetSystemCounter();
	}
    ISR_LEAVE();
}

#endif//OS_ISR_H