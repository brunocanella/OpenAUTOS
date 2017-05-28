#ifndef OSEK_RESOURCES_H
#define OSEK_RESOURCES_H

#include "types.h"
#include "../resource.h"


/**
 * DeclareResource serves as an external declaration of a resource. The function and use of this service are similar to that of the external declaration of variables.
 *
 * @param[in] ResourceIdentifier Resource identifier (Duh).
 */
#define DeclareResource( ResourceIdentifier ) extern ResourceType ##ResourceIdentifier;

/**
 * This call serves to enter critical sections in the code that are assigned to the resource referenced by ResID. A critical section shall always be left using ReleaseResource.
 *
 * @remark The OSEK priority ceiling protocol for resource management is described in chapter 8.5.
 * @remark Nested resource occupation is only allowed if the inner critical sections are completely executed within the surrounding critical section (strictly stacked, see chapter 8.2, Restrictions when using resources). Nested occupation of one and the same resource is also forbidden!
 * @remark It is recommended that corresponding calls to GetResource and ReleaseResource appear within the same function.
 * @remark It is not allowed to use services which are points of rescheduling for non preemptable tasks (TerminateTask, ChainTask, Schedule and WaitEvent, see chapter 4.6.2) in critical sections. Additionally, critical sections are to be left before completion of an interrupt service routine.
 * @remark Generally speaking, critical sections should be short.
 * @remark The service may be called from an ISR and from task level (see Figure 12-1).
 *
 * @param[in] ResID Reference to resource
 *
 * @return [Standard] No error, E_OK.
 * @return [Extended] Resource <ResID> is invalid, E_OS_ID.
 * @return [Extended] Attempt to get a resource which is already occupied by any task or ISR, or the statically assigned priority of the calling task or interrupt routine is higher than the calculated ceiling priority, E_OS_ACCESS
 */
StatusType GetResource( ResourceType ResID );

/**
 * ReleaseResource is the counterpart of GetResource and serves to leave critical sections in the code that are assigned to the resource referenced by ResID.
 *
 * @param[in] ResID Reference to resource.
 *
 * @remark For information on nesting conditions, see particularities of GetResource.
 * @remark The service may be called from an ISR and from task level (see Figure 12-1).
 * 
 * @return [Standard] No error, E_OK.
 * @return [Extended] Resource <ResID> is invalid, E_OS_ID.
 * @return Attempt to release a resource which is not occupied by any task or ISR, or another resource shall be released before, E_OS_NOFUNC.
 * @return Attempt to release a resource which has a lower ceiling priority than the statically assigned priority of the calling task or interrupt routine, E_OS_ACCESS.
 */
StatusType ReleaseResource( ResourceType ResID );

/**Constant of data type ResourceType (see chapter 8, Resource management).*/
extern const ResourceType RES_SCHEDULER;

#endif//OSEK_RESOURCES_H