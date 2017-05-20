#ifndef OSEK_TASKS_H
#define OSEK_TASKS_H

#include "types.h"

////////////////////////////////////////////////////////////////////////////////
//  Data Types
////////////////////////////////////////////////////////////////////////////////

/**This data type identifies a task.*/
typedef uint8_t TaskType;
/**This data type points to a variable of TaskType.*/
typedef TaskType* TaskRefType;
/**This data type identifies the state of a task.*/
typedef uint8_t TaskStateType;
/**This data type points to a variable of the data type TaskStateType.*/
typedef TaskStateType* TaskStateRefType;

////////////////////////////////////////////////////////////////////////////////
//  Constants
////////////////////////////////////////////////////////////////////////////////

/**
 * Constant of data type TaskStateType for task state running.
 * @remark In the running state, the CPU is assigned to the task, so that its instructions can be executed. Only one task can be in this state at any point in time, while all the other states can be adopted simultaneously by several tasks.
 */
#define RUNNING 1
/**
 * Constant of data type TaskStateType for task state waiting.
 * @remark A task cannot continue execution because it shall wait for at least one event (see chapter 7, Event mechanism).
 */
#define WAITING 2
/**
 * Constant of data type TaskStateType for task state ready.
 * @remark All functional prerequisites for a transition into the running state exist, and the task only waits for allocation of the processor. The scheduler decides which ready task is executed next. 
 */
#define READY 3
/**
 * Constant of data type TaskStateType for task state suspended.
 * @remark In the suspended state the task is passive and can be activated.
 */
#define SUSPENDED 4
/**
 * Constant of data type TaskType for a not defined task.
 */
#define INVALID_TASK 255

////////////////////////////////////////////////////////////////////////////////
//  Constructional Elements
////////////////////////////////////////////////////////////////////////////////

/**
 * DeclareTask serves as an external declaration of a task. The
 * function and use of this service are similar to that of the external
 * declaration of variables.
 */
#define DeclareTask( TaskIdentifier ) extern Task##TaskIdentifier()

#define TASK( TaskName ) StatusType Func##TaskName(void)

////////////////////////////////////////////////////////////////////////////////
//  System Services
////////////////////////////////////////////////////////////////////////////////

/**
 * The task TaskID is transferred from the suspended state into the ready state. The operating system ensures that the task code is being executed from the first statement.
 *
 * @remark When an extended task is transferred from suspended state into ready state all its events are cleared.
 *
 * @remark The service may be called from interrupt level and from task level (see Figure 12-1). Rescheduling after the call to ActivateTask depends on the place it is called from (ISR, non preemptable task, preemptable task).
 *
 * If E_OS_LIMIT is returned the activation is ignored.
 *
 * @param TaskID[in] Task reference
 * 
 * @return [Standard] No error, E_OK.
 * @return [Extended] Too many task activations of TaskID, E_OS_LIMIT
 * @return [Extended] Task TaskID is invalid, E_OS_ID
 * 
 * @remark [Conformance] BCC1, BCC2, ECC1, ECC2
 */
StatusType ActivateTask( TaskType TaskID );

/**
 * This service causes the termination of the calling task. The calling task is transferred from the running state into the suspended state.
 *
 * @remark An internal resource assigned to the calling task is automatically released. Other resources occupied by the task shall have been released before the call to TerminateTask. If a resource is still occupied in standard status the behaviour is undefined.
 * @remark If the call was successful, TerminateTask does not return to the call level and the status can not be evaluated. If the version with extended status is used, the service returns in case of error, and provides a status which can be evaluated in the application. If the service TerminateTask is called successfully, it enforces a rescheduling.
 * @remark Ending a task function without call to TerminateTask or ChainTask is strictly forbidden and may leave the system in an undefined state.
 *
 * @return Task still occupies resources, E_OS_RESOURCE
 * @return Call at interrupt level, E_OS_CALLEVEL
 */
StatusType TerminateTask( void );

/**
 * This service causes the termination of the calling task. After termination of the calling task a succeeding task <TaskID> is activated. Using this service, it ensures that the succeeding task starts to run at the earliest after the calling task has been terminated.
 *
 * @remark If the succeeding task is identical with the current task, this does not result in multiple requests. The task is not transferred to the suspended state, but will immediately become ready again.
 * @remark An internal resource assigned to the calling task is automatically released, even if the succeeding task is identical with the current task. Other resources occupied by the calling shall have been released before ChainTask is called. If a resource is still occupied in standard status the behaviour is undefined.
 * @remark If called successfully, ChainTask does not return to the call level and the status can not be evaluated.
 * @remark In case of error the service returns to the calling task and provides a status which can then be evaluated in the application.
 * @remark If the service ChainTask is called successfully, this enforces a rescheduling.
 * @remark Ending a task function without call to TerminateTask or ChainTask is strictly forbidden and may leave the system in an undefined state.
 * @remark If E_OS_LIMIT is returned the activation is ignored. When an extended task is transferred from suspended state into ready state all its events are cleared.
 *
 * @param TaskID[in] Reference to the sequential succeeding task to be activated.
 *
 * @return [Standard] No return to call level.
 * @return [Standard] Too many task activations of <TaskID>, E_OS_LIMIT.
 * @return [Extended] Task <TaskID> is invalid, E_OS_ID.
 * @return [Extended] Calling task still occupies resources, E_OS_RESOURCE.
 * @return [Extended] Call at interrupt level, E_OS_CALLEVEL.
 */
StatusType ChainTask( TaskType TaskID );

/**
 * GetTaskID returns the information about the TaskID of the task which is currently running.
 * 
 * @remark Allowed on task level, ISR level and in several hook routines (see Figure 12-1).
 * @remark This service is intended to be used by library functions and hook routines.
 * @remark If <TaskID> can’t be evaluated (no task currently running), the service returns INVALID_TASK as TaskType.
 *
 * @param TaskID[out] Reference to the task which is currently running.
 *
 * @return [Standard] No error, E_OK
 * @return [Extended] No error, E_OK
 */
StatusType GetTaskID( TaskRefType TaskID );

/**
 * Returns the state of a task (running, ready, waiting, suspended) at the time 
 * of calling GetTaskState.
 *
 * @remark The service may be called from interrupt service routines, task level, and some hook routines (see Figure 12-1).
 * @remark When a call is made from a task in a full preemptive system, the result may already be incorrect at the time of evaluation.
 * @remark When the service is called for a task, which is activated more than once, the state is set to running if any instance of the task is running.
 *
 * @param TaskID[in] Task reference
 * @param State[out] Reference to the state of the task TaskID
 *
 * @return [Standard] No error, E_OK
 * @return [Extended] Task TaskID is invalid, E_OS_ID
 */
StatusType GetTaskState( TaskType TaskID, TaskStateRefType State );

/**
 * If a higher-priority task is ready, the internal resource of the task is released, the current task is put into the ready state, its context is saved and the higher-priority task is executed. Otherwise the calling task is continued.
 *
 * @remark Rescheduling only takes place if the task an internal resource is assigned to the calling task during system generation. For these tasks, Schedule enables a processor assignment to other tasks with lower or equal priority than the ceiling priority of the internal resource and higher priority than the priority of the calling task in application-specific locations. When returning from Schedule, the internal resource has been taken again. This service has no influence on tasks with no internal resource assigned (preemptable tasks).
 *
 * @return [Standard] No error, E_OK.
 * @return [Extended] Call at interrupt level, E_OS_CALLEVEL
 * @return [Extended] Calling task occupies resources, E_OS_RESOURCE
 */
StatusType Schedule( void );

#endif//OSEK_TASKS_H
