#ifndef OSEK_EVENTS_H
#define OSEK_EVENTS_H

#include "types.h"
#include "tasks.h"

typedef uint8_t EventMaskType;

typedef EventMaskType* EventMaskRefType;

/**
 * DeclareEvent serves as an external declaration of an event. The function and use of this service are similar to that of the external declaration of variables.
 *
 * @param[in] EventIdentifier Event identifier (C-identifier).
 */
#define DeclareEvent( EventIdentifier ) extern EventMaskType ##EventIdentifier

/**
 * The service may be called from an interrupt service routine and from the task level, but not from hook routines.
 * 
 * The events of task <TaskID> are set according to the event mask Mask. Calling SetEvent causes the task TaskID to be transferred to the ready state, if it was waiting for at least one of the events specified in <Mask>.
 * 
 * @remark Any events not set in the event mask remain unchanged.
 *
 * @param[in] TaskID Reference to the task for which one or several events are to be set.
 * @param[in] Mask Mask of the events to be set
 *
 * @return [Standard] No error, E_OK.
 * @return [Extended] Task <TaskID> is invalid, E_OS_ID.
 * @return [Extended] Referenced task is no extended task, E_OS_ACCESS.
 * @return [Extended] Events can not be set as the referenced task is in the suspended state, E_OS_STATE.
 */
StatusType SetEvent( TaskType TaskID, EventMaskType Mask );

/**
 * The events of the extended task calling ClearEvent are cleared according to the event mask <Mask>.
 * 
 * @remark The system service ClearEvent is restricted to extended tasks which own the event.
 * 
 * @param[in]  Mask  The mask
 *
 * @return [Standard] No error, E_OK.
 * @return [Extended] Call not from extended task, E_OS_ACCESS.
 * @return [Extended] Call at interrupt level, E_OS_CALLEVEL.
 */
StatusType ClearEvent( EventMaskType Mask );

/**
 * This service returns the current state of all event bits of the task TaskID, not the events that the task is waiting for.
 *
 * The service may be called from interrupt service routines, task level and some hook routines (see Figure 12-1).
 *
 * The current status of the event mask of task TaskID is copied to Event.
 *
 * The referenced task shall be an extended task.
 *
 * @remark The referenced task shall be an extended task.
 *
 * @param[in] TaskID Task whose event mask is to be returned.
 * @param[out] Reference to the memory of the return data.
 *
 * @return [Standard] No error, E_OK.
 * @return [Extended] Task TaskID is invalid, E_OS_ID.
 * @return [Extended] Referenced task TaskID is not an extended task, E_OS_ACCESS.
 * @return [Extended] Referenced task TaskID is in the suspended state, E_OS_STATE.
 */
StatusType GetEvent( TaskType TaskID, EventMaskRefType Event );

/**
 * The state of the calling task is set to waiting, unless at least one of the events specified in <Mask> has already been set.
 *
 * @remark This call enforces rescheduling, if the wait condition occurs. If rescheduling takes place, the internal resource of the task is released while the task is in the waiting state.
 * @remark This service shall only be called from the extended task owning the event.
 *
 * @param[in] Mask Mask of the events waited for.
 * 
 * @return [Standard] No error, E_OK.
 * @return [Extended] Calling task is not an extended task, E_OS_ACCESS.
 * @return [Extended] Calling task occupies resources, E_OS_RESOURCE.
 * @return [Extended] Call at interrupt level, E_OS_CALLEVEL.
 */
StatusType WaitEvent( EventMaskType Mask );

#endif//OSEK_EVENTS_H