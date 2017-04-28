#if defined(PLATFORM) &&  PLATFORM == PIC18F25K80
#include "platform/pic18f25k80/constants.h"
#elif defined(PLATFORM) && PLATFORM == LINUX
#include "platform/linux/constants.h"
#else
#error Platform not defined!
#endif

#define HIGH PLATFORM_HIGH
#define LOW PLATFORM_LOW

#define ON PLATFORM_ON
#define OFF PLATFORM_OFF

#define INPUT PLATFORM_INPUT
#define OUTPUT PLATFORM_OUTPUT

#ifndef NULL
#define NULL PLATFORM_NULL
#endif

#ifndef TRUE
#define TRUE  (1==1)
#endif

#ifndef FALSE
#define FALSE (!TRUE)
#endif
