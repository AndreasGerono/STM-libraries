#include "clicker.h"


#define DEFAULT_TIME 150
#define MINIMUM_TIME 50
#define  DEBOUNCE_TIME 10
#define ACCELERATION 10 




static void debounce(Button *btn) {
  if (btn->debounceFlag) {
    event_reset(&btn->event);
    btn->event.interval = DEBOUNCE_TIME;
    btn->debounceFlag = RESET;
  }
}

Button clicker_make(GPIO_TypeDef *gpio, uint16_t pin, void (*func)()) {
  Button btn;
  btn.pin = pin;
  btn.gpio = gpio;
  btn.clickFlag = RESET;
  btn.debounceFlag = SET;
  btn.timing = DEFAULT_TIME;
  btn.buttonFunc = func;
  btn.event = event_make(btn.timing);
  return btn;
}

void clicker_check(Button *button) {
  if (!HAL_GPIO_ReadPin(button->gpio, button->pin))
    button->clickFlag = SET;
  else {
    button->timing = DEFAULT_TIME;
    button->clickFlag = RESET;
    button->debounceFlag = SET;
  }
  if (button->clickFlag) {
    debounce(button);
    if (event_State(&button->event)) {
      button->buttonFunc();
      button->event.interval = button->timing;
      if (button->timing > MINIMUM_TIME)
       button->timing -= ACCELERATION;
    }
  }
}