#include <stdint.h>

TASK( task_init ) {
	TRISB = 0x00; // Output Lower Bits
	LATB = 0x00;

	ActivateTask( task_rb0 );
	ActivateTask( task_rb1 );
	ActivateTask( task_rb2 );
	ActivateTask( task_off );
	TerminateTask();
}

#define _XTAL_FREQ 64000000

void delei( uint8_t s ) {
	while( s > 0 ) {
		s--;
		for( uint8_t i = 0; i < 100; i++ ) {
			__delay_ms(10);
		}
	}
}

TASK( task_rb0 ) {
	while( TRUE ) {
		LATBbits.LATB0 = 1;
		//delei(1);
	}
}

TASK( task_rb1 ) {
	while( TRUE ) {
		LATBbits.LATB1 = 1;
		//delei(1);
	}
}

TASK( task_rb2 ) {
	while( TRUE ) {
		LATBbits.LATB2 = 1;
		//delei(1);
	}
}

TASK( task_off ) {	
	while( TRUE ) {		
		//delei(1);
		LATB = 0;
	}
}
