#include <stdint.h>

#define _XTAL_FREQ 64000000

void delay_s( uint8_t s ) {
	while( s > 0 ) {
		s--;
		for( uint8_t i = 0; i < 100; i++ ) {
			__delay_ms(10);
		}
	}
}

TASK( task_init ) {
	TRISB = 0x00; // Output Lower Bits
	LATB = 0x00;

	while( TRUE ) {
		ActivateTask( task_start );		
	}
}

TASK( task_start ) {		
	ActivateTask( task_rb0 );
	ActivateTask( task_rb1 );
	ActivateTask( task_rb2 );	
	LATB = 0;
	__delay_ms(10);
	TerminateTask();
}

TASK( task_rb0 ) {
	LATBbits.LATB0 = 1;
	__delay_ms(10);
	TerminateTask();
}

TASK( task_rb1 ) {
	LATBbits.LATB1 = 1;
	__delay_ms(10);
	TerminateTask();
}

TASK( task_rb2 ) {
	LATBbits.LATB2 = 1;
	__delay_ms(10);
	TerminateTask();
}