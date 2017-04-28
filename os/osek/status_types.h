#ifndef OSEK_STATUS_TYPES_H
#define OSEK_STATUS_TYPES_H

#include "types.h"

/**
 * Normal return value.
 * 
 * If the only possible return status is E_OK, the implementation is free not to return a status.
 */
extern const StatusType E_OK;

/*All errors of API services*/
extern const StatusType E_OS_ACCESS;
extern const StatusType E_OS_CALLEVEL;
extern const StatusType E_OS_ID;
extern const StatusType E_OS_LIMIT;
extern const StatusType E_OS_NOFUNC;
extern const StatusType E_OS_RESOURCE;
extern const StatusType E_OS_STATE;
extern const StatusType E_OS_VALUE;

#endif//OSEK_STATUS_TYPES_H
