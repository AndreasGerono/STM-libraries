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
	task->interval = interval_ms;
	task->taskFunc = func;
	task->lastTick = 0;
	return task;
}

void task_check(Task task, void *args) {
	if ((HAL_GetTick() - task->lastTick >= task->interval) && task->lastTick) {
		task->lastTick = HAL_GetTick();
		task->taskFunc(args);
	}
}

void task_reset(Task task) {
	task->lastTick = HAL_GetTick();
}

void task_stop(Task task){
	task->lastTick = 0;
}

void task_destroy(Task task){
	free(task);
}


Event event_make(uint32_t interval_ms) {
	Event event = malloc(sizeof * event);
	event->interval = interval_ms;
	event->lastTick = 0;
	return event;
}

_Bool event_state(Event event) {
	if ((HAL_GetTick() - event->lastTick >= event->interval) && event->lastTick) {
		event->lastTick = HAL_GetTick();
		return 1;
	}
	return 0;
}

void event_reset(Event event) {
	while((event->lastTick = HAL_GetTick()) == RESET);
}

void event_change(Event event, uint32_t interval){
	event->interval = interval;
}

void event_stop(Event event){
	event->lastTick = 0;
}

void event_destroy(Event event){
	free(event);
}
