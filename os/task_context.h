#ifndef OS_TASK_CONTEXT_H
#define OS_TASK_CONTEXT_H

#if defined(PLATFORM) &&  PLATFORM == PIC18F25K80
#include "platform/pic18f25k80/task_context.h"
#else
#error Platform not defined!
#endif

typedef PlatformTaskContextType TaskContextType;
typedef PlatformTaskContextRefType TaskContextRefType;

#define SaveTaskContext( TaskContextRef ) PlatformSaveTaskContext( (TaskContextRef) )

#define LoadTaskContext( TaskContextRef ) PlatformLoadTaskContext( (TaskContextRef) )

#endif//OS_TASK_CONTEXT_H