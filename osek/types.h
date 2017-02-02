#ifndef TYPES_H
#define TYPES_H

////////////////////////////////////////////////////////////////////////////////
//  Common
////////////////////////////////////////////////////////////////////////////////

/**
 * This data type is used for all status information the API services offer.
 */
typedef int StatusType;

////////////////////////////////////////////////////////////////////////////////
//  Task Managment
////////////////////////////////////////////////////////////////////////////////


/**This data type identifies a task.*/
typedef int TaskType;
/**This data type points to a variable of TaskType.*/
typedef TaskType* TaskRefType;
/**This data type identifies the state of a task.*/
typedef int TaskStateType;
/**This data type points to a variable of the data type TaskStateType.*/
typedef TaskStateType* TaskStateRefType;



#endif//TYPES_H
