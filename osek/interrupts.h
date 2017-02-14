#ifndef INTERRUPTS_H
#define INTERRUPTS_H

/**
 * This service restores the state saved by DisableAllInterrupts.
 * @remark The service may be called from an ISR category 1 and category 2 and from the task level, but not from hook routines.
 * @remark This service is a counterpart of DisableAllInterrupts service, which has to be called before, and its aim is the completion of the critical section of code. No API service calls are allowed within this critical section.
 * @remark The implementation should adapt this service to the target hardware providing a minimum overhead. Usually, this service enables recognition of interrupts by the central processing unit.
*/
void EnableAllInterrupts( void );

/**
 * This service disables all interrupts for which the hardware supports disabling. The state before is saved for the EnableAllInterrupts call.
 * 
 * @remark The service may be called from an ISR category 1 and category 2 and from the task level, but not from hook routines.
 * @remark This service is intended to start a critical section of the code. 
 * @remark This section shall be finished by calling the EnableAllInterrupts service. No API service calls are allowed within this critical section.
 * @remark The implementation should adapt this service to the target hardware providing a minimum overhead. Usually, this service disables recognition of interrupts by the central processing unit.
 * @remark Note that this service does not support nesting. If nesting is needed for critical sections e.g: for libraries SuspendOSInterrupts/ResumeOSInterrupts or SuspendAllInterrupt/ResumeAllInterrupts should be used.
 */
void DisableAllInterrupts( void );


/**
 * This service restores the recognition status of all interrupts saved by the SuspendAllInterrupts service.
 * 
 * @remark The service may be called from an ISR category 1 and category 2, from alarm-callbacks and from the task level, but not from all hook routines.
 * @remark This service is the counterpart of SuspendAllInterrupts service, which has to have been called before, and its aim is the completion of the critical section of code. No API service calls beside SuspendAllInterrupts/ResumeAllInterrupts pairs and SuspendOSInterrupts/ResumeOSInterrupts pairs are allowed within this critical section.
 * @remark The implementation should adapt this service to the target hardware providing a minimum overhead. 
 * @remark SuspendAllInterrupts/ResumeAllInterrupts can be nested. In case of nesting pairs of the calls SuspendAllInterrupts and ResumeAllInterrupts the interrupt recognition status saved by the first call of SuspendAllInterrupts is restored by the last call of the ResumeAllInterrupts service.
 */
void ResumeAllInterrupts( void );

/**
 * This service saves the recognition status of all interrupts and disables all interrupts for which the hardware supports disabling.
 * @remark The service may be called from an ISR category 1 and category 2, from alarm-callbacks and from the task level, but not from all hook routines.
 * @remark This service is intended to protect a critical section of code from interruptions of any kind. This section shall be finished by calling the ResumeAllInterrupts service. No API service calls beside SuspendAllInterrupts/ResumeAllInterrupts pairs and SuspendOSInterrupts/ResumeOSInterrupts pairs are allowed within this critical section.
 * @remark The implementation should adapt this service to the target hardware providing a minimum overhead.
 */
void SuspendAllInterrupts( void );

/**
 * This service restores the recognition status of interrupts saved by the SuspendOSInterrupts service.
 * 
 * @remark The service may be called from an ISR category 1 and category 2 and from the task level, but not from hook routines.
 * @remark This service is the counterpart of SuspendOSInterrupts service, which has to have been called before, and its aim is the completion of the critical section of code. No API service calls beside SuspendAllInterrupts/ResumeAllInterrupts pairs and SuspendOSInterrupts/ResumeOSInterrupts pairs are allowed within this critical section.
 * @remark The implementation should adapt this service to the target hardware providing a minimum overhead.
 * @remark SuspendOSInterrupts/ResumeOSInterrupts can be nested. In case of nesting pairs of the calls SuspendOSInterrupts and ResumeOSInterrupts the interrupt recognition status saved by the first call of SuspendOSInterrupts is restored by the last call of the ResumeOSInterrupts service.
 */
void ResumeOSInterrupts( void );

/**
 * This service saves the recognition status of interrupts of category 2 and disables the recognition of these interrupts.
 * @remark The service may be called from an ISR and from the task level, but not from hook routines.
 * @remark This service is intended to protect a critical section of code. This section shall be finished by calling the ResumeOSInterrupts service. No API service calls beside SuspendAllInterrupts/ResumeAllInterrupts pairs and SuspendOSInterrupts/ResumeOSInterrupts pairs are allowed within this critical section.
 * @remark The implementation should adapt this service to the target hardware providing a minimum overhead.
 * @remark It is intended only to disable interrupts of category 2. However, if this is not possible in an efficient way more interrupts may be disabled.
 */
void SuspendOSInterrupts( void );

// #define ISR(FuncName) void Isr##FuncName()

#endif//INTERRUPTS_H