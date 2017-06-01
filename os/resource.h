#ifndef OS_RESOURCE_H
#define OS_RESOURCE_H

#include "types.h"

/**Constant used to indicate the beginning of the linked list*/
const uint8_t RESOURCE_ID_LIST_START = UINT8_MAX;

/**Type for the Resource Id*/
typedef uint8_t ResourceType;
/**Type for the Resource ceiling Priority*/
typedef uint8_t ResourceDataPriorityType;

/**
 * @brief The structure that stores data about the resource. Also serves as a linked list node
 * 
 * @remark Due to an odd bug with the xc8 1.37 compiler, where he does not allow it to declare an extern const
 * as the size of an array (altough it works sometimes), I changed the model to use "movable" nodes with linked lists.
 * 
 * Basically, every Task and ISR has a variable which is used as the start of its own linked list. There is also a
 * global variable (g_resources) which is the main linked list for resources.
 * 
 * Initially, all resources are allocated to the g_resources linked list. When a Task or ISR requests a resource,
 * it is moved from g_resources to the linked list in the Task/ISR. When this resource is released, it is put back
 * in the g_resources list.
 */
typedef struct SResourceDataType {
	ResourceType id;                    ///< The unique identifier for this resource.
	ResourceDataPriorityType priority;  ///< The ceiling priority for this resource
    struct SResourceDataType* next;     ///< Link to the next node
    struct SResourceDataType* prev;     ///< Link to the previous node
} ResourceDataType;
/**Type for pointers of the ResourceDataType*/
typedef ResourceDataType* ResourceDataRefType;

void InitializeResourceDataList( ResourceDataRefType List );
void AddResourceDataToResources( ResourceDataRefType Resource, ResourceType ResID, ResourceDataPriorityType Priority );

/**
 * A linked list to the resources of this project.
 */
extern ResourceDataType g_resources;

/**
 * Finds the resource with ResID in the given list
 */
ResourceDataRefType FindResource( ResourceDataRefType First, ResourceType ResID );
/**
 * Moves the resource with ResID from one linked list to another.
 */
void MoveResourceData( ResourceType ResID, ResourceDataRefType From, ResourceDataRefType To );

/**
 * TODO: Check if multiple critical sections need to be implemented
 */
extern uint8_t g_is_resource_critical_section;

void SetResourceCriticalSection();
void ReleaseResourceCriticalSection();
uint8_t IsResourceCriticalSection();

#endif //OS_RESOURCE_H