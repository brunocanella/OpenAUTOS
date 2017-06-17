#define LED_GREEN PORTBbits.RB0
#define LED_YELLOW PORTBbits.RB1
#define LED_RED PORTBbits.RB2
#define LED_RED_READ LATBbits.LATB2

TASK( task_init ) {
    TRISBbits.TRISB0 = OUTPUT;
    TRISBbits.TRISB1 = OUTPUT;
    TRISBbits.TRISB2 = OUTPUT;

    LED_GREEN = LOW;
    LED_YELLOW = LOW;
    LED_RED = LOW;
    ChainTask( task_green );
}

TASK( task_green ) {
	while( TRUE ) {
		LED_GREEN = HIGH;
		ActivateTask( task_yellow );
		LED_GREEN = LOW;
		ActivateTask( task_yellow );		
	}
}

TASK( task_yellow ) {
	LED_YELLOW = HIGH;
	ActivateTask( task_red );
	LED_YELLOW = LOW;
	ActivateTask( task_red );
	TerminateTask();
}

TASK( task_red ) {
	LED_RED = !LED_RED_READ;
	TerminateTask();
}
