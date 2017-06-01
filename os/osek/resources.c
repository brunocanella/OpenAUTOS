#include "resources.h"
#include "../task.h"

#include "status_types.h"

StatusType GetResource( ResourceType ResID ) {
    if( g_active_task == NULL ) {
        // TODO: DEBUG_ERROR
        RESET();
    }    
    ResourceDataRefType l_resource = FindResource( &g_resources, ResID );
    // If the resource you are attempting to get is not found here, then an error code will be returned!
    if( l_resource == NULL) {
        TaskDataRefType l_task;
        for( uint8_t i = 0; i < TASKS_TOTAL; i++ ) {
            l_task = &g_tasks[i];
            l_resource = FindResource( &l_task->resources, ResID );
            if( l_resource != NULL ) {
                break;
            }
        }
        if( l_resource == NULL ) { // Resource ID is invalid!
            return E_OS_ID;
        } 
        // Attempt to get a resource which is already occupied by any task or ISR
        return E_OS_ACCESS;
    }
    // Ok, so we found the resource. Now a quick test before moving it to the task:
     // The statically assigned priority of the calling task or interrupt routine is higher than the calculated ceiling priority
	 if( g_active_task->priority > l_resource->priority ) {
	 	return E_OS_ACCESS;
	 }    
    // Move it from the Resources List to the Task List
    MoveResourceData( ResID, &g_resources, &g_active_task->resources );
    g_active_task->priority = l_resource->priority;
    
    SetResourceCriticalSection();

	return E_OK;
}

StatusType ReleaseResource( ResourceType ResID ) {
	// Check the resource stack to see if the released resource matches the top one.
	// Free the resource
	// Call Scheduler - check if a new task would assume
    
    if( g_active_task == NULL ) {
        // TODO: DEBUG_ERROR
        RESET();
    }    
    // First, tries to find the resource at the active task (most likely to find here)
    ResourceDataRefType l_resource = FindResource( &g_active_task->resources, ResID );
    // If the resource you are attempting to get is not found in the active task, then an error code will be returned!
    if( l_resource == NULL) {
        TaskDataRefType l_task;
        for( uint8_t i = 0; i < TASKS_TOTAL; i++ ) {
            l_task = &g_tasks[i];
            if( l_task == g_active_task ) {
                continue;
            }
            l_resource = FindResource( &l_task->resources, ResID );
            if( l_resource != NULL ) {
                break;
            }
        }
        if( l_resource == NULL ) { // Tries to find it one last time in the Resources list
            l_resource = FindResource( &g_resources, ResID );
            if( l_resource == NULL ) { // Resource <ResID> is invalid, E_OS_ID
                return E_OS_ID;
            }
            // Attempt to release a resource which is not occupied by any task or ISR
            return E_OS_NOFUNC;
        }
        // Attempt to release a resource which is already occupied by a task or ISR
        return E_OS_ACCESS;
    }    
    //-------------------    
    // Another resource shall be released before
    if( l_resource->next != NULL ) { // l_resource has to be the last item in the list (top of the stack)
       return E_OS_NOFUNC; 
    }
    // Attempt to release a resource which has a lower ceiling priority than the statically assigned priority of the calling task or interrupt routine
    if( l_resource->priority < g_active_task->priority ) {
       return E_OS_ACCESS;
    }
    
    MoveResourceData( ResID, &g_active_task->resources, &g_resources );
    
    l_resource = &g_active_task->resources;
    while( l_resource->next != NULL ) {
        l_resource = l_resource->next;
    }
    if( l_resource->prev == NULL ) { // No more resources allocated
        g_active_task->priority = g_active_task->priority_base;
    } else {
        g_active_task->priority = l_resource->priority;
    }
    
    ReleaseResourceCriticalSection();
	
	return Schedule();
}
