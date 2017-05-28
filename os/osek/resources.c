#include "resources.h"
#include "../task.h"

#include "status_types.h"



StatusType GetResource( ResourceType ResID ) {
	// ResourceDataRefType l_resource = FindResource( ResID );
	// // Resource ID is invalid!
	// if( l_resource == NULL ) {
	// 	return E_OS_ID;
	// }

	// if( g_active_task == NULL ) {
	// 	// TODO: DEBUG_ERROR
	// 	RESET();
	// }

	// TaskDataRefType l_task;
	// // Attempt to get a resource which is already occupied by any task or ISR
	// for( uint8_t i = 0; i < TASKS_TOTAL; i++ ) {
	// 	l_task = &g_tasks[i];
	// 	for( uint8_t j = 0; j < l_task->resource_stack_top; j++ ) {
	// 		if( l_task->resource_stack[j]->id == ResID ) {
	// 			return E_OS_ACCESS;
	// 		}
	// 	}
	// }
	
	// // The statically assigned priority of the calling task or interrupt routine is higher than the calculated ceiling priority
	// if( g_active_task->priority > l_resource->priority ) {
	// 	return E_OS_ACCESS;
	// }

	// g_active_task->priority = l_resource->priority;
	// g_active_task->resource_stack[g_active_task->resource_stack_top] = l_resource;
	// g_active_task->resource_stack_top++;

	// SetResourceCriticalSection();

	return E_OK;
}

StatusType ReleaseResource( ResourceType ResID ) {
	// Check the resource stack to see if the released resource matches the top one.
	// Free the resource
	// Call Scheduler - check if a new task would assume

	
	// ResourceDataRefType l_resource = FindResource( ResID );
	// // Resource ID is invalid!
	// if( l_resource == NULL ) {
	// 	return E_OS_ID;
	// }

	// TaskDataRefType l_task;
	// uint8_t l_found = FALSE;
	// // Attempt to get a resource which is already occupied by any task or ISR
	// for( uint8_t i = 0; i < TASKS_TOTAL; i++ ) {
	// 	l_task = &g_tasks[i];
	// 	for( uint8_t j = 0; j < l_task->resource_stack_top; j++ ) {
	// 		if( l_task->resource_stack[j]->id == ResID ) {
	// 			l_found = TRUE;
	// 			break;
	// 		}
	// 	}
	// }
	// // Attempt to release a resource which is not occupied by any task or ISR
	// if( l_found == FALSE ) {
	// 	return E_OS_NOFUNC;
	// }    
	// // Another resource shall be released before
	// if( l_task->resource_stack[(uint8_t)(l_task->resource_stack_top-1)]->id != ResID ) {
	// 	return E_OS_NOFUNC;
	// }
	// // Attempt to release a resource which has a lower ceiling priority than the statically assigned priority of the calling task or interrupt routine
	// if( l_resource->priority < l_task->priority ) {
	// 	return E_OS_ACCESS;
	// }

	// l_task->resource_stack_top--;
	// // If we have no more resources allocated, we restore the original priority
	// if( l_task->resource_stack_top == 0 ) {
	// 	l_task->priority = l_task->priority_base;
	// } else {
	// 	l_task->priority = l_task->resource_stack[(uint8_t)(l_task->resource_stack_top-1)]->priority;
	// }

	// ReleaseResourceCriticalSection();
	
	return E_OK;
}
