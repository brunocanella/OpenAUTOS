#ifndef HOOKS_H
#define HOOKS_H

#include "types.h"

////////////////////////////////////////////////////////////////////////////////
//  Data Types
////////////////////////////////////////////////////////////////////////////////

/**This data type represents the identification of system services.*/
typedef int OSServiceIdType;

////////////////////////////////////////////////////////////////////////////////
//  System Services
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief This hook routine is called by the operating system at the end of a system service which returns StatusType not equal E_OK. It is called before returning to the task level.
 * @brief This hook routine is called when an alarm expires and an error is detected during task activation or event setting.
 * @brief The ErrorHook is not called, if a system service called from ErrorHook does not return E_OK as status value. Any error by calling of system services from the ErrorHook can only be detected by evaluating the status value.
 *
 * @remark See chapter 11.1 for general description of hook routines.
 *
 * @param[in] Error The Error occurred.
 */
void ErrorHook( StatusType Error );

/**
 * This hook routine is called by the operating system before executing a new task, but after the transition of the task to the running state (to allow evaluation of the TaskID by GetTaskID).
 * 
 * @remark See chapter 11.1 for general description of hook routines.
 */
void PreTaskHook( void );

/**
 * This hook routine is called by the operating system after executing the current task, but before leaving the task's running state (to allow evaluation of the TaskID by GetTaskID).
 *
 * @remark See chapter 11.1 for general description of hook routines.
 */
void PostTaskHook( void );

/**
 * This hook routine is called by the operating system at the end of the operating system initialisation and before the scheduler is running. At this time the application can initialise device drivers etc.
 *
 * @remark See chapter 11.1 for general description of hook routines.
 */
void StartupHook( void );

/**
 * This hook routine is called by the operating system when the OS service ShutdownOS has been called. This routine is called during the operating system shut down.
 *
 * @remark ShutdownHook is a hook routine for user defined shutdown functionality, see chapter 11.4.
 *
 * @param[in] Error Error occurred
 */
void ShutdownHook( StatusType Error );

////////////////////////////////////////////////////////////////////////////////
//  Constants
////////////////////////////////////////////////////////////////////////////////

// unique identifier of system service xx.  Example: OSServiceId_ActivateTask. OSServiceId_xx is of type OSServiceIdType.
//const OSServiceIdType OSServiceId_xx;

////////////////////////////////////////////////////////////////////////////////
//  Macros
////////////////////////////////////////////////////////////////////////////////

// provides the service identifier where the error has been risen. The service identifier is of type OsServiceIdType. Possible values are OSServiceId_xx, where xx is the name of the system service.
//#define OSErrorGetServiceId

// names of macros to access (within ErrorHook) parameters of the system service which called ErrorHook, where x1 is the name of the system service and x2 is the parameter name.
// #define OSError_x1_x2

#endif//HOOKS_H