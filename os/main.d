
void main(void) {
	InitializeTasks();
	InititializeResources();

	StartOS( 0 );

	while( 1 ) { NOP(); }

	return;
}
