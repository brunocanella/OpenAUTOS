#include "setup.h"

#if defined(PLATFORM) &&  PLATFORM == PIC18F25K80
#include "platform/pic18f25k80/setup.h"
#else
#error Platform not declared
#endif

void Setup() {
	PlatformSetup();
}