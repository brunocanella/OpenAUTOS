#include "resource.h"
#include "constants.h"

// ResourceDataType g_resources[RESOURCES_TOTAL+1];

ResourceDataRefType FindResource( ResourceType ResID ) {
	// for( uint8_t i = 0; i <= RESOURCES_TOTAL; i++ ) {
	// 	if( g_resources[i].id == ResID ) {
	// 		return &g_resources[i];
	// 	}
	// }

	// return NULL;
}

// uint8_t g_is_resource_critical_section = 0;

void SetResourceCriticalSection() {
	// g_is_resource_critical_section++;
}

void ReleaseResourceCriticalSection() {
	// g_is_resource_critical_section--;
}

uint8_t IsResourceCriticalSection() {
	// return g_is_resource_critical_section;
}