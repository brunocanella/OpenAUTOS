#ifndef OS_OPENAUTOS
#define OS_OPENAUTOS

#include "constants.h"
#include "debugger.h"
#include "isr.h"
#include "setup.h"
#include "system_counter.h"
#include "task.h"
#include "task_context.h"
#include "task_metadata.h"
#include "types.h"

#include "osek/os.h"

#if defined(PLATFORM) &&  PLATFORM == PIC18F25K80
#include <xc.h>
#else
#error Platform not declared
#endif

#endif//OS_OPENAUTOS