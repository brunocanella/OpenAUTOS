#include "task_context.h"

StatusType ResetTaskContext( PlatformTaskContextRefType Context ) {
	// Erasing data members
	Context->work = 0;
	Context->bsr = 0;
	Context->status = 0;
	Context->stack_top = 0;
	// Erasing the context stack
	uint24_t* l_stack_ptr = Context->stack;
	for( uint8_t i = 0; i < PLATFORM_CONTEXT_STACK_SIZE; i++ ) {
		l_stack_ptr[i] = 0;
	}

	return E_OK;
}
