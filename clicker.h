#include "stdint.h"
#include "stm32l0xx_hal.h"


typedef void (*funcptr)(void *args);

typedef struct ButtonElement* Button;
Button button_make(GPIO_TypeDef *gpio, uint16_t pin, funcptr);
_Bool button_check(Button, void *args);

