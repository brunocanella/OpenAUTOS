#ifndef PIC18F25K80_SYSTEM_COUNTER_H
#define PIC18F25K80_SYSTEM_COUNTER_H

#include "../../types.h"

void PlatformResetSystemCounter();

void PlatformInitializeSystemCounter();

uint8_t PlatformHasInterruptSystemCounter();

#endif//PIC18F25K80_SYSTEM_COUNTER_H