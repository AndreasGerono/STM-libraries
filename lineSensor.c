
#include "lineSensor.h"
#include "tim.h"

#define SENSOR_LED_GPIO GPIOB
#define CHARGE_TIME 10
#define NR_OF_SENSORS 2
#define BLACK_TRESHOLD 1000

#define TIMER TIM7
#define TIMER_HANDLER &htim7

_Bool startFlag;
_Bool nextFlag;
_Bool lastFlag;

static uint16_t sensorPin[] = {SENSOR1_Pin, SENSOR2_Pin};

static GPIO_TypeDef *sensorGpio[] = {SENSOR1_GPIO_Port, SENSOR2_GPIO_Port};

static uint16_t ledPin[] = {LED0_Pin, LED0_Pin};
static GPIO_TypeDef *ledGpio[] = {LED0_GPIO_Port, LED0_GPIO_Port};

static uint8_t currentSensor = 0;
static uint16_t sensorValues[8];

_Bool sensor_get(uint8_t sensor) {
  if (sensorValues[sensor] >= BLACK_TRESHOLD)
    return 1;
  else
    return 0;
}

static void outputMode(uint8_t sensor) {
  GPIO_InitTypeDef GPIO_InitStruct;
  GPIO_InitStruct.Pin = sensorPin[sensor];
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  HAL_GPIO_Init(sensorGpio[sensor], &GPIO_InitStruct);
}

static void inputMode(uint8_t sensor) {
  GPIO_InitTypeDef GPIO_InitStruct;
  GPIO_InitStruct.Pin = sensorPin[sensor];
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  HAL_GPIO_Init(sensorGpio[sensor], &GPIO_InitStruct);
}

static void startMeasure() {
  startFlag = RESET;
  nextFlag = SET;
  outputMode(currentSensor);
  sensorGpio[currentSensor]->BSRR = sensorPin[currentSensor];
  ledGpio[currentSensor]->BSRR = ledPin[currentSensor];
  TIMER->CNT = RESET;
  HAL_TIM_Base_Start_IT(TIMER_HANDLER);
}

static void finishMeasure() {
  sensorValues[currentSensor] = TIMER->CNT;
  HAL_TIM_Base_Stop_IT(TIMER_HANDLER);
  startFlag = SET;
  lastFlag = RESET;
  ledGpio[currentSensor]->BRR = ledPin[currentSensor];
  printf("%d\n", sensorValues[currentSensor]); //uwaga zatrzyma mcu w nie debag
  currentSensor++;
}

void sensor_timeOut(){
  HAL_TIM_Base_Stop_IT(TIMER_HANDLER);
  sensorValues[currentSensor] = BLACK_TRESHOLD;
  startFlag = SET;
  lastFlag = RESET;
}

void sensor_trigger() {
  startFlag = SET;
  currentSensor = 0;
}

void sensor_measure() {
  if (currentSensor < NR_OF_SENSORS) {
    if (startFlag)
      startMeasure();
    else if (nextFlag && (TIMER->CNT >= CHARGE_TIME)) {
      nextFlag = RESET;
      lastFlag = SET;
      inputMode(currentSensor);
      TIMER->CNT = RESET;      
    }
    else if (lastFlag && !HAL_GPIO_ReadPin(sensorGpio[currentSensor], sensorPin[currentSensor]))
      finishMeasure();
  }
}

