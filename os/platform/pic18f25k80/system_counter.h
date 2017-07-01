#ifndef PIC18F25K80_SYSTEM_COUNTER_H
#define PIC18F25K80_SYSTEM_COUNTER_H

#include "../../types.h"

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