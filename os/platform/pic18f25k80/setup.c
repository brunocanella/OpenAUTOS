#include "setup.h"
#include "system_counter.h"

#include <xc.h>

void PlatformInitializeOscillator() {
    OSCCONbits.IRCF = 0b111; // 16MHz x4 (PLL) => 64MHz
    OSCTUNEbits.PLLEN = 1;
}

void PlatformSetup() {	
	PlatformInitializeOscillator();
}