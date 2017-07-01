#include "task_context.h"

uint8_t _wreg;
uint8_t _bsr;
uint8_t _status;

StatusType ResetTaskContext( PlatformTaskContextRefType Context, CallbackType Callback ) {
	// Erasing data members
	Context->work = 0;
	Context->bsr = 0;
	Context->status = 0;	
	// Erasing the context stack
	uint32_t* l_stack_ptr = Context->stack;
	for( uint8_t i = 0; i < PLATFORM_CONTEXT_STACK_SIZE; i++ ) {
		l_stack_ptr[i] = 0;
	}
	l_stack_ptr[0] = (PlatformTaskContextStackType) Callback;
	Context->stack_top = 1;

	return E_OK;
}
