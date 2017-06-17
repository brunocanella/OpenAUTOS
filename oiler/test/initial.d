const TaskType TaskType_task1 = 1;
TASK(task1);
const TaskType TaskType_task2 = 2;
TASK(task2);
const TaskType TaskType_task3 = 3;
TASK(task3);

const ResourceType ResourceType_Resource1 = 1;
const ResourceType ResourceType_Resource2 = 2;
const ResourceType ResourceType_Resource3 = 3;
const ResourceType ResourceType_Resource4 = 4;
const ResourceType ResourceType_Resource5 = 5;

void TASK_FUNC_IDLE() {
	while( TRUE ) { NOP(); }
}

void InitializeTasks() {
	InitializeTaskData( g_idle, TASK_ID_IDLE, 0, READY, TASK_FUNC_IDLE );
	InitializeTaskData( &g_tasks[0], TaskType_task1, 1, SUSPENDED, TASK_FUNC_task1 );
	InitializeTaskData( &g_tasks[1], TaskType_task2, 2, SUSPENDED, TASK_FUNC_task2 );
	InitializeTaskData( &g_tasks[2], TaskType_task3, 8, SUSPENDED, TASK_FUNC_task3 );
	GroupTasksSamePriority();
}

ResourceDataType g_res[5];
void InititializeResources() {
	AddResourceDataToResources( &g_res[0], ResourceType_Resource1, 3 );
	AddResourceDataToResources( &g_res[1], ResourceType_Resource2, 3 );
	AddResourceDataToResources( &g_res[2], ResourceType_Resource3, 3 );
	AddResourceDataToResources( &g_res[3], ResourceType_Resource4, 0 );
	AddResourceDataToResources( &g_res[4], ResourceType_Resource5, 0 );
}

asm("GLOBAL _TASK_FUNC_IDLE, _TASK_FUNC_task1, _TASK_FUNC_task2, _TASK_FUNC_task3" );
