#include "resource.h"
#include "constants.h"

ResourceDataType g_resources;

void InitializeResourceDataList( ResourceDataRefType List ) {
    List->id = RESOURCE_ID_LIST_START;
    List->priority = RESOURCE_ID_LIST_START;
    List->next = NULL;
    List->prev = NULL;
}

void AddResourceDataToResources( ResourceDataRefType Resource, ResourceType ResID, ResourceDataPriorityType Priority ) {
    ResourceDataRefType l_resources = &g_resources;
    while( l_resources->next != NULL ) {
        l_resources = l_resources->next;
    }
    l_resources->next = Resource;
    Resource->prev = l_resources;
    Resource->next = NULL;
    Resource->id = ResID;
    Resource->priority = Priority;
}

ResourceDataRefType FindResource( ResourceDataRefType First, ResourceType ResID ) {
    ResourceDataRefType l_resource = First;
    while( l_resource != NULL ) {
        if( l_resource->id == ResID ) {
            break;
        }
        l_resource = l_resource->next;
    }
    return l_resource;
}

void MoveResourceData( ResourceType ResID, ResourceDataRefType From, ResourceDataRefType To ) {
    if( ResID == RESOURCE_ID_LIST_START ) {
        return;
    }
    while( From != NULL ) {
        if( From->id == ResID ) {
            break;
        }
        From = From->next;
    }
    if( From == NULL ) { // ResID not found in the "From" list
        return;
    }
    // Remove the node from the From list (prev is at least RESOURCE_ID_NULL, which means it is the initial node)
    // Case 1: prev = yes, next = no; From is the last node in the list, so just remove the reference from the previous
    if( From->next == NULL ) {
        From->prev->next = NULL;
    // Case 2: prev = yes, next = yes; From a middle node, so link from->prev with from->next;
    } else {
        From->prev->next = From->next;
        From->next->prev = From->prev;
    }
    // Now, Set the "From" node to the end of the To node
    while( To->next != NULL ) {
        To = To->next;
    }
    To->next = From;
    From->prev = To;
    From->next = NULL;    
}

uint8_t g_is_resource_critical_section = 0;

void SetResourceCriticalSection() {
	g_is_resource_critical_section++;
}

void ReleaseResourceCriticalSection() {
	g_is_resource_critical_section--;
}

uint8_t IsResourceCriticalSection() {
	return g_is_resource_critical_section;
}