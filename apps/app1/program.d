TASK( task_init ) {
	TRISB = 0x00; // Output Lower Bits
	LATB = 0x00;

    ChainTask( task_start );
}

#define _XTAL_FREQ 64000000

TASK( task_rb0 ) {
	LATBbits.LATB0 = 1;
	__delay_ms(1);
	ChainTask(task_start);	
}

TASK( task_rb1 ) {
	LATBbits.LATB1 = 1;
	__delay_ms(1);
	TerminateTask();
}

TASK( task_rb2 ) {
	LATBbits.LATB2 = 1;
	__delay_ms(1);
	TerminateTask();
}

TASK( task_start ) {
	LATB = 0;
	__delay_ms(1);
	ActivateTask( task_rb0 );
	ActivateTask( task_rb1 );
	ActivateTask( task_rb2 );
	TerminateTask();
}
