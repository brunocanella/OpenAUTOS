#ifndef OS_TASK_H
#define OS_TASK_H

#include "constants.h"
#include "osek/tasks.h"   // TaskType
#include "osek/events.h"  // EventMaskType
#include "task_context.h"
#include "resource.h"

const uint8_t TASK_ID_IDLE = 0;

extern const uint8_t TASKS_TOTAL;

/**Type for task priority*/
typedef uint8_t TaskPriorityType;
/**Type for task callback method*/
typedef CallbackType TaskCallbackType;

typedef struct SEventData {                                 ///< Groups all the event-related variables of a task
        EventMaskType flag;                                 ///< Used by SetEvent to flag an event.
        EventMaskType wait;                                 ///< Used by WaitEvent to flag an event wait.
} EventsDataType;

typedef EventsDataType* EventsDataTypeRef;


/**
 * This type represents a Task in the operating system.
 */
typedef struct STaskDataType {
	TaskType id;											///< Task "unique" identifier. Actually, this indicates the "type" of the task.
	TaskPriorityType priority;								///< Current priority of the task
	TaskPriorityType priority_base;							///< Original priority of the task (Resets to this value after releasing a resource).
	TaskStateType state;									///< Current state of the task (RUNNING, WAITING, SUSPENDED or READY).
	TaskContextType context;								///< The context of the task. Used for prempting tasks.
	TaskCallbackType callback;								///< The "body" of the task.
	struct STaskDataType* next_task_same_priority;			///< Links together tasks that have the same priority.    	
    ResourceDataType resources;                             ///< Keeps a stack of the resources allocated, in order to know the next resource that shall be released.
    EventsDataType events;                                  ///< Groups all the event-related variables of a task
} TaskDataType;
/**A pointer type for tasks*/
typedef TaskDataType* TaskDataRefType;

/**
 * Initializes a TaskData item passed by reference.
 */
void InitializeTaskData( TaskDataRefType Task, TaskType Id, TaskPriorityType Priority, TaskStateType State, TaskCallbackType Callback );

/**
 * Groups tasks with the same priority for the Round-Robin Scheduler.
 */
void GroupTasksSamePriority();

extern TaskDataType g_tasks[];

extern TaskDataRefType g_idle;

extern TaskDataRefType g_active_task;

#endif//OS_TASK_H