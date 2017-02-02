#ifndef SCHEDULERS_H
#define SCHEDULERS_H

#include "types.h"

/**
 * If a higher-priority task is ready, the internal resource of the task is 
 * released, the current task is put into the ready state, its context is saved
 * and the higher-priority task is executed. Otherwise the calling task is 
 * continued.
 *
 * @remark Rescheduling only takes place if the task an internal resource is assigned to the calling task during system generation. For
these tasks, Schedule enables a processor assignment to other tasks with lower or equal priority than the ceiling priority of the
internal resource and higher priority than the priority of the calling task in application-specific locations. When returning
from Schedule, the internal resource has been taken again. This service has no influence on tasks with no internal resource
assigned (preemptable tasks).
 *
 * @return [Standard] No error, E_OK.
 * @return [Extended] Call at interrupt level, E_OS_CALLEVEL
 * @return [Extended] Calling task occupies resources, E_OS_RESOURCE
 */
StatusType Schedule( void );


#endif//SCHEDULERS_H
