#include "task_metadata.h"

#include <xc.h>

#include "debugger.h"
#include "constants.h"

TaskMetaDataType g_task_metadata[TASKS_TOTAL_TYPES];

TaskMetaDataRefType GetTaskMetaDataRef( TaskType TaskID ) {
	for( uint8_t i = 0; i < TASKS_TOTAL_TYPES; i++ ) {
		TaskMetaDataRefType l_curr = &g_task_metadata[i];
		if( l_curr->id == TaskID ) {
			return l_curr;
		}
	}

	// If the metadata was not found, then something went VERY wrong. We are going to reset the
	// device, but before, we log an error to the devs.
	LOGGER_ERROR(("ERROR[GetTaskMetaDataRef]! Metadata was not found!"));
	OS_RESET();

	// To avoid compilation errors
	return NULL;
}