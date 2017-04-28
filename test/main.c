//#include <pic18f25k80.h>
#include <xc.h>
#include <stdint.h>

#define OUTPUT 0
#define INPUT 1

#define LOW 0
#define HIGH 1

void main(void) {
    
    TRISDbits.RD0 = OUTPUT;

    PORTDbits.RD0 = LOW;
    
    while( 1 ) {
    	for( uint8_t i = 0; i < 20000; i++ ) {
        	asm("nop");
    	}
    	PORTDbits.RD0 = !LATDbits.LATD0;
    }
    
    return;
}
