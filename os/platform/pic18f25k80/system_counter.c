#include "system_counter.h"

#include <xc.h>

void PlatformResetSystemCounter() {
    INTCONbits.TMR0IF = 0; // Interrupt Flag Off (so it didn't happen yet)
    TMR0 = 49536; // 65536 - 16000 == 1 ms timeout (p/ 64MHz FOSC => FOSC/4 == 16MHz)
}

void PlatformInitializeSystemCounter() {
    T0CONbits.PSA = 1; // DON'T Use prescaler
    T0CONbits.T0PS = 0b111; // 1:256 => whatever... it will be 1:1 because bypass scalar (PSA) is enabled
    T0CONbits.T0CS = 0; // Transition == Internal Clock (The other mode is external counter on T0CKI)
    T0CONbits.T08BIT = 0; // 16 bits timer (max 2^16 ticks)
    T0CONbits.TMR0ON = 1; // ON

    PlatformResetSystemCounter();
    INTCONbits.TMR0IE = 1; // Timer 0  On        
}

uint8_t PlatformHasInterruptSystemCounter() {
	return INTCONbits.TMR0IE && INTCONbits.TMR0IF;
}