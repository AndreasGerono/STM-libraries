#include "tasker.h"
#include <stdlib.h>

Task task_make(uint32_t interval_ms, void (*func)()) {
  Task task;
  task.interval = interval_ms;
  task.lastTick = HAL_GetTick();
  task.taskFunc = func;
  return task;
}

void task_check(Task *task) {
  if (HAL_GetTick() - task->lastTick >= task->interval) {
    task->lastTick = HAL_GetTick();
    task->taskFunc();
  }
}

void task_reset(Task *task) {
  task->lastTick = HAL_GetTick();
}

void task_destroy(Task *task){
  free(task);
}


Event event_make(uint32_t interval_ms) {
  Event event;
  event.interval = interval_ms;
  event.lastTick = HAL_GetTick();
  return event;
}

_Bool event_State(Event *event) {
  if (HAL_GetTick() - event->lastTick >= event->interval) {
    event->lastTick = HAL_GetTick();
    return 1;
  } else
    return 0;
}

void event_reset(Event *event) {
  event->lastTick = HAL_GetTick();
}

void event_destroy(Event *event){
  free(event);
}