#include "clicker.h"
#include "tasker.h"
#include "stdlib.h"

#define DEFAULT_TIME 200
#define  DEBOUNCE_TIME 100

enum State{
	Stop = 0,
	Debounce,
	Click,
} State;

struct ButtonElement{
	uint16_t pin;
	GPIO_TypeDef *gpio;
	enum State state;
	Task task;
};


void setClick(Button);
void setStop(Button);
void setDebounce(Button);

static void debounceAction(Button instance){
	task_change(instance->task, DEBOUNCE_TIME);
	task_reset(instance->task);
}

static void clickAction(Button instance){
	task_change(instance->task, DEFAULT_TIME);
}

static void stopAction(Button instance){
	task_stop(instance->task);
}


Button button_make(GPIO_TypeDef *gpio, uint16_t pin, funcptr funn){
	Button instance = malloc( sizeof * instance);
	if (NULL != instance){
		instance->gpio = gpio;
		instance->pin = pin;
		instance->task = task_make(DEFAULT_TIME, funn);
		instance->state = Stop;
	}
	return instance;
}

_Bool button_check(Button instance, void *args){
	if(!HAL_GPIO_ReadPin(instance->gpio, instance->pin)){
		setDebounce(instance);
	}
	else {
		setStop(instance);
	}
	if (task_state(instance->task, args)){
		setClick(instance);
		return SET;
	}
	return RESET;
}


void setStop(Button instance){
	if (instance->state == Click){
		instance->state = Stop;
		stopAction(instance);
	}
}

void setClick(Button instance){
	if (instance->state == Debounce){
		instance->state = Click;
		clickAction(instance);
	}
}

void setDebounce(Button instance){
	if (instance->state == Stop){
		instance->state = Debounce;
		debounceAction(instance);
	}
}





