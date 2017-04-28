#ifndef OS_TASK_H
#define OS_TASK_H

#include "constants.h"
#include "osek/tasks.h"
#include "task_context.h"

extern const uint8_t TASKS_TOTAL;

/**Type for task priority*/
typedef uint8_t TaskPriorityType;
/**Type for task callback method*/
typedef void (*TaskCallbackType)(void);

typedef struct {
	TaskType id;
	TaskPriorityType priority;	
	TaskStateType state;
	TaskContextType context;
	TaskCallbackType callback;
} TaskDataType;

typedef TaskDataType* TaskDataRefType;

extern TaskDataType g_tasks[TASKS_TOTAL+1];

extern TaskDataRefType g_idle;

extern TaskDataRefType g_active_task;

#define TASKID_IDLE 0

//
// OpenAUTOS
// 
void InitializeIdleTask();

#endif//OS_TASK_H