const uint8_t TASKS_TOTAL = 7;

const TaskType task_rx = 1;
TASK(task_rx);
const TaskType task_farol = 2;
TASK(task_farol);
const TaskType task_seta = 3;
TASK(task_seta);
const TaskType task_volante = 4;
TASK(task_volante);
const TaskType task_velocidade = 5;
TASK(task_velocidade);
const TaskType task_sentido = 6;
TASK(task_sentido);
const TaskType task_init = 7;
TASK(task_init);

const ResourceType res_a = 1;

#define _XTAL_FREQ 64000000

void TASK_FUNC_IDLE() {
	while( TRUE ) {
#ifdef _XTAL_FREQ
		__delay_us(10);
#endif
		Schedule();
	}
}

void InitializeTasks() {
	InitializeTaskData( g_idle, TASK_ID_IDLE, 0, READY, TASK_FUNC_IDLE );
	InitializeTaskData( &g_tasks[0], task_rx, 3, SUSPENDED, TASK_FUNC_task_rx );
	InitializeTaskData( &g_tasks[1], task_farol, 2, SUSPENDED, TASK_FUNC_task_farol );
	InitializeTaskData( &g_tasks[2], task_seta, 2, SUSPENDED, TASK_FUNC_task_seta );
	InitializeTaskData( &g_tasks[3], task_volante, 2, SUSPENDED, TASK_FUNC_task_volante );
	InitializeTaskData( &g_tasks[4], task_velocidade, 2, SUSPENDED, TASK_FUNC_task_velocidade );
	InitializeTaskData( &g_tasks[5], task_sentido, 2, SUSPENDED, TASK_FUNC_task_sentido );
	InitializeTaskData( &g_tasks[6], task_init, 254, READY, TASK_FUNC_task_init );
	GroupTasksSamePriority();
}

ResourceDataType g_res[1];
void InititializeResources() {
	AddResourceDataToResources( &g_res[0], res_a, 255 );
}

asm("GLOBAL _TASK_FUNC_IDLE, _TASK_FUNC_task_rx, _TASK_FUNC_task_farol, _TASK_FUNC_task_seta, _TASK_FUNC_task_volante, _TASK_FUNC_task_velocidade, _TASK_FUNC_task_sentido, _TASK_FUNC_task_init" );
