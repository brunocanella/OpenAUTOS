#ifndef OS_INTERRUPTS
#define OS_INTERRUPTS

#if defined(PLATFORM) &&  PLATFORM == PIC18F25K80
#include "platform/pic18f25k80/interrupts.h"
#else
#error Platform not declared
#endif

#define ENABLE_GLOBAL_INTERRUPTS PLATFORM_ENABLE_GLOBAL_INTERRUPTS
#define DISABLE_GLOBAL_INTERRUPTS PLATFORM_DISABLE_GLOBAL_INTERRUPTS

#define ENABLE_ROUNDROBIN_SCHEDULER PLATFORM_ENABLE_ROUNDROBIN_SCHEDULER
#define DISABLE_ROUNDROBIN_SCHEDULER PLATFORM_DISABLE_ROUNDROBIN_SCHEDULER

#define IS_ON_INTERRUPT PLATFORM_IS_ON_INTERRUPT

#endif//OS_INTERRUPTS