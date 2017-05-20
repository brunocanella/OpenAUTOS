#include "resources.h"

#include "status_types.h"

StatusType GetResource( ResourceType ResID ) {
	return E_OK;
}

StatusType ReleaseResource( ResourceType ResID ) {
	// Check the resource stack to see if the released resource matches the top one.
	// Free the resource
	// Call Scheduler - check if a new task would assume
	
	return E_OK;
}