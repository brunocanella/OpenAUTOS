#ifndef OS_H
#define OS_H

#include "types.h"

/**This data type represents the application mode.*/
typedef int AppModeType;

/**
 * This service returns the current application mode. It may be used to write mode dependent code.
 * 
 * @remark See chapter 5 for a general description of application modes.
 * @remark Allowed for task, ISR and all hook routines.
 *
 * @return The current application mode.
 */
AppModeType GetActiveApplicationMode( void );

/**
 * The user can call this system service to start the operating system in a specific mode, see chapter 5, Application modes.
 *
 * @remark Only allowed outside of the operating system, therefore implementation specific restrictions may apply. See also chapter 11.3, System start-up, especially with respect to systems where OSEK and OSEKtime coexist. This call does not need to return.
 *
 * @param[in] Mode The application mode to start the OS.
 */
void StartOS( AppModeType Mode );

/**
 * @brief The user can call this system service to abort the overall system (e.g. emergency off). The operating system also calls this function internally, if it has reached an undefined internal state and is no longer ready to run.
 * @brief If a ShutdownHook is configured the hook routine ShutdownHook is always called (with <Error> as argument) before shutting down the operating system. If ShutdownHook returns, further behaviour of ShutdownOS is implementation specific.
 * @brief In case of a system where OSEK OS and OSEKtime OS coexist, ShutdownHook has to return.
 * @brief <Error> needs to be a valid error code supported by OSEK OS. In case of a system where OSEK OS and OSEKtime OS coexist, <Error> might also be a value accepted by OSEKtime OS. In this case, if enabled by an OSEKtime configuration parameter, OSEKtime OS will be shut down after OSEK OS shutdown.
 *
 * @remark After this service the operating system is shut down.
 * @remark Allowed at task level, ISR level, in ErrorHook and StartupHook, and also called internally by the operating system.
 * @remark If the operating system calls ShutdownOS it never uses E_OK as the passed parameter value.
 *
 * @param[in]  Error  The error
 */
void ShutdownOS( StatusType Error );

/**Default application mode, always a valid parameter to StartOS.*/
extern const AppModeType OSDEFAULTAPPMODE;

#endif//OS_H