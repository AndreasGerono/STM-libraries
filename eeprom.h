//
// eeprom.h
// Created by Andreas Gerono on 11/03/2020.

#ifndef _eeprom_h_
#define _eeprom_h_

#include "stdint.h"

uint32_t eeprom_read (uint32_t address);
void eeprom_write (uint32_t address, uint32_t value);
void eeprom_initit();


#endif