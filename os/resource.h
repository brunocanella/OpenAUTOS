#ifndef OS_RESOURCE_H
#define OS_RESOURCE_H

#include "types.h"

/**The total amount of resources in the project*/
//extern const uint8_t RESOURCES_TOTAL;

/**Type for the Resource Id*/
typedef uint8_t ResourceType;

typedef struct SResourceDataType {
	ResourceType id;
	uint8_t priority;
} ResourceDataType;

typedef ResourceDataType* ResourceDataRefType;

// extern ResourceDataType g_resources[RESOURCES_TOTAL+1];

// ResourceDataRefType FindResource( ResourceType ResID );

// extern uint8_t g_is_resource_critical_section;

// void SetResourceCriticalSection();
// void ReleaseResourceCriticalSection();
// uint8_t IsResourceCriticalSection();

#endif //OS_RESOURCE_H