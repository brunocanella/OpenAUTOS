#ifndef OS_TASK_H
#define OS_TASK_H

#include "constants.h"
#include "osek/tasks.h"
#include "task_context.h"
#include "resource.h"

extern const uint8_t TASKS_TOTAL;

/**Type for task priority*/
typedef uint8_t TaskPriorityType;
/**Type for task callback method*/
typedef CallbackType TaskCallbackType;

typedef uint8_t TaskResourceStackTop;


typedef struct STaskDataType {
	TaskType id;											///< Task "unique" identifier. Actually, this indicates the "type" of the task.
	TaskPriorityType priority;								///< Current priority of the task
	TaskPriorityType priority_base;							///< Original priority of the task (Resets to this value after releasing a resource).
	TaskStateType state;									///< Current state of the task (RUNNING, WAITING, SUSPENDED or READY).
	TaskContextType context;								///< The context of the task. Used for prempting tasks.
	TaskCallbackType callback;								///< The "body" of the task.
	struct STaskDataType* next_task_same_priority;			///< Links together tasks that have the same priority.    
	TaskResourceStackTop resource_stack_top;				///< Tracks the index of the top of the stack.
    ResourceDataRefType resource_stack[10];	///< Keeps a stack of the resources allocated, in order to know the next resource that shall be released.
} TaskDataType;

typedef TaskDataType* TaskDataRefType;

extern TaskDataType g_tasks[];

extern TaskDataRefType g_idle;

extern TaskDataRefType g_active_task;

#define TASKID_IDLE 0

//
// OpenAUTOS
// 
void IdleTask_Callback();
void InitializeIdleTask();

#endif//OS_TASK_H