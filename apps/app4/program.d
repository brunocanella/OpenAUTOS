#include <stdint.h>

#define _XTAL_FREQ 64000000

#define EVENT_SYNC 0b00000001

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

	GetResource( res_a );
		ActivateTask( task_rb0 );
		ActivateTask( task_rb1 );
		ActivateTask( task_rb2 );
	ReleaseResource( res_a );

	while( TRUE ) {
		SetEvent( task_rb2, EVENT_SYNC );
		LATB = 0x00;
		delay_s(1);
	}
}

TASK( task_rb0 ) {
	while( TRUE ) {
		WaitEvent( EVENT_SYNC );
		ClearEvent( EVENT_SYNC );
		LATBbits.LATB0 = 1;
		delay_s(1);
	}
}

TASK( task_rb1 ) {
	while( TRUE ) {
		WaitEvent( EVENT_SYNC );
		ClearEvent( EVENT_SYNC );
		LATBbits.LATB1 = 1;
		delay_s(1);
		SetEvent( task_rb0, EVENT_SYNC );
	}
}

TASK( task_rb2 ) {
	while( TRUE ) {
		WaitEvent( EVENT_SYNC );
		ClearEvent( EVENT_SYNC );
		LATBbits.LATB2 = 1;
		delay_s(1);
		SetEvent( task_rb1, EVENT_SYNC );
	}
}
