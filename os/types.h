#ifndef OS_TYPES_H
#define OS_TYPES_H

#if defined(PLATFORM) &&  PLATFORM == PIC18F25K80
#include <stdint.h>
#else
#error Failed to define Standard Types.
#endif

/**
 * Base type for 
 */
typedef uint8_t StatusType;

#include "osek/status_types.h"

#endif//OS_TYPES_H