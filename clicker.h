
#include "stateMachine.h"
#include "stdint.h"


typedef void (*buttonFuncptr)(); 

typedef struct {
  uint16_t pin;
  GPIO_TypeDef *gpio;
  _Bool clickFlag;
  _Bool debounceFlag;
  Event event;
  uint8_t timing;
  buttonFuncptr buttonFunc;
} Button;


static void skipClick(Button *btn);
Button clicker_make(GPIO_TypeDef *gpio, uint16_t pin, void (*func)());
void clicker_check(Button *button);