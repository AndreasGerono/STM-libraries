//
//library for managing time tasks/events
//

//for functions with parameter use events, task can only manage void functions!!
//events use with 'if' function in main loop
//You need start task/event with *_reset()

#include "stdint.h"


typedef void (*taskFuncptr)(void *args);

typedef struct TaskElement *Task;
typedef struct EventElenemt *Event;


Task task_make(uint32_t interval_ms, taskFuncptr);
void task_reset(Task);
void task_stop(Task);
void task_check(Task, void *args);

Event event_make(uint32_t intermal_ms);
void event_reset(Event);
void event_stop(Event);
void event_change(Event, uint32_t interval_ms);
_Bool event_state(Event);





