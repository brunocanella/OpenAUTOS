#ifndef PIC18F25K80_SYSTEM_COUNTER_H
#define PIC18F25K80_SYSTEM_COUNTER_H

#include "../../types.h"

#include <xc.h>

#define PlatformStopScheduler() do{TMR0ON = 0;}while(0)
#define PlatformResumeScheduler() do{if(TMR0 > 65000){TMR0 -= 160;} TMR0ON = 1;}while(0)

/**
 * Performs the reset of the system counter in this platform.
 */
void PlatformResetSystemCounter();

/**
 * Performs the initialization of the system clock in this platform.
 */
void PlatformInitializeSystemCounter();

/**
 * Checks if there is an interruption due to countdown in this platform.
 */
uint8_t PlatformHasInterruptSystemCounter();

#endif//PIC18F25K80_SYSTEM_COUNTER_H