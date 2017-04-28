#ifndef OS_TASK_METADATA_H
#define OS_TASK_METADATA_H

#include "task.h"

extern const uint8_t TASKS_TOTAL_TYPES;

typedef uint8_t TaskActivationsType;

typedef struct {
	TaskType id;
	TaskActivationsType activations;
	TaskActivationsType current_active;	
} TaskMetaDataType;

typedef TaskMetaDataType* TaskMetaDataRefType;

extern TaskMetaDataType g_task_metadata[TASKS_TOTAL_TYPES];

#endif//OS_TASK_METADATA_H