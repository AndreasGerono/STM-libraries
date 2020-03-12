//
// eeprom.c
// Created by Andreas Gerono on 11/03/2020.

#include "eeprom.h"
#include "stm32l0xx_hal.h"

#define EEPROM_START 0x08080000
#define EEPROM_SIZE 1024

uint32_t eeprom_read (uint32_t address){
	address += EEPROM_START;
	return (*(__IO uint32_t *)address);
}


void eeprom_write(uint32_t address, uint32_t value){
	address += EEPROM_START;
	HAL_FLASHEx_DATAEEPROM_Program (FLASH_TYPEPROGRAMDATA_WORD, address, value);
}


void eeprom_initit(){
	HAL_FLASHEx_DATAEEPROM_Unlock();
	HAL_FLASHEx_DATAEEPROM_EnableFixedTimeProgram(); //??
}