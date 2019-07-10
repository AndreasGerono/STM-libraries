#include "tasker.h"
#include "stdlib.h"
#include "stm32l0xx_hal.h"



struct TaskElement{
	uint32_t interval;
	uint32_t lastTick;
	taskFuncptr taskFunc;
};

struct EventElenemt{
	uint32_t interval;
	uint32_t lastTick;
};


Task task_make(uint32_t interval_ms, taskFuncptr func) {
	Task task = malloc( sizeof * task);
	if (NULL != task){
		task->interval = interval_ms;
		task->taskFunc = func;
		task->lastTick = 0;
	}
	return task;
}

void task_change(Task task, uint32_t interval){
	task->interval = interval;
}

_Bool task_state(Task task, void *args) {
	if ((HAL_GetTick() - task->lastTick >= task->interval) && task->lastTick) {
		task->lastTick = HAL_GetTick();
		if (NULL != task->taskFunc)
			task->taskFunc(args);
		return SET;
	}
	return RESET;
}

void task_reset(Task task) {
	while((task->lastTick = HAL_GetTick()) == 0);	//Protects against Tick == 0 => stop condition
}

void task_stop(Task task){
	task->lastTick = 0;
}

void task_destroy(Task task){
	free(task);
}

