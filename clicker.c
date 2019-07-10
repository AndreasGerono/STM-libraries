#include "clicker.h"
#include "clicker.h"
#include "tasker.h"
#include "stdlib.h"

#define DEFAULT_TIME 300
#define  DEBOUNCE_TIME 100

int debugger1 = 100;

enum State{
	Stop = 0,
	Debounce,
	Click,
} State;

struct ButtonElement{
	uint16_t pin;
	GPIO_TypeDef *gpio;
	enum State state;
	Event event;
};


void setClick(Button);
void setStop(Button);
void setDebounce(Button);

static void debounceAction(Button instance){
	event_change(instance->event, DEBOUNCE_TIME);
	event_reset(instance->event);
}

static void clickAction(Button instance){
	event_change(instance->event, DEFAULT_TIME);
}

static void stopAction(Button instance){
	event_stop(instance->event);
	debugger1++;
}


Button button_make(GPIO_TypeDef *gpio, uint16_t pin){
	Button instance = malloc( sizeof * instance);
	instance->gpio = gpio;
	instance->pin = pin;
	instance->event = event_make(DEFAULT_TIME);
	instance->state = Click;	//starting with click to force setStop in first button_check
	return instance;
}

_Bool button_check(Button instance){
	debugger1 = instance->state;
	if(!HAL_GPIO_ReadPin(instance->gpio, instance->pin)){
		setDebounce(instance);
	}
	else {
		setStop(instance);
	}
	if (event_state(instance->event)){
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





