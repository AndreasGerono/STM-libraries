//
// HD47780 controller with 4-bit mode
//

#include "hd44780.h"
#include "stdint.h"

#define delay10US(us)                                  \
  do {                                                 \
    asm volatile("MOV R0,%[loops]\n                 \
                 1: \n                             \
                 SUB R0, #1\n                      \
                 CMP R0, #0\n                      \
                 BNE 1b \t" \
                 :                                     \
                 : [loops] "r"(50 * us)                \
                 : "memory");                          \
  } while (0)

#define _BV(bit) (1 << (bit))

//
//
//

static void _LCD_OutNibble(uint8_t nibbleToWrite) {
  if (nibbleToWrite & _BV(0))
    LCD_DB4_GPIO_Port->BSRR = LCD_DB4_Pin;
  else
    LCD_DB4_GPIO_Port->BRR = LCD_DB4_Pin;

  if (nibbleToWrite & _BV(1))
    LCD_DB5_GPIO_Port->BSRR = LCD_DB5_Pin;
  else
    LCD_DB5_GPIO_Port->BRR = LCD_DB5_Pin;

  if (nibbleToWrite & _BV(2))
    LCD_DB6_GPIO_Port->BSRR = LCD_DB6_Pin;
  else
    LCD_DB6_GPIO_Port->BRR = LCD_DB6_Pin;

  if (nibbleToWrite & _BV(3))
    LCD_DB7_GPIO_Port->BSRR = LCD_DB7_Pin;
  else
    LCD_DB7_GPIO_Port->BRR = LCD_DB7_Pin;
}

//
// Write to display
//

void _LCD_Write(uint8_t dataToWrite) {
  LCD_E_GPIO_Port->BSRR = LCD_E_Pin;
  _LCD_OutNibble(dataToWrite >> 4);
  LCD_E_GPIO_Port->BRR = LCD_E_Pin;
  LCD_E_GPIO_Port->BSRR = LCD_E_Pin;
  _LCD_OutNibble(dataToWrite);
  LCD_E_GPIO_Port->BRR = LCD_E_Pin;
  delay10US(10);
}

//
// Write command to display
//

void LCD_WriteCommand(uint8_t commandToWrite) {
  LCD_RS_GPIO_Port->BRR = LCD_RS_Pin;
  _LCD_Write(commandToWrite);
}

//
// Write data to display
//

void LCD_WriteData(uint8_t dataToWrite) {
  LCD_RS_GPIO_Port->BSRR = LCD_RS_Pin;
  _LCD_Write(dataToWrite);
}

//
// Write string to display
//

void LCD_WriteText(char *text) {
  while (*text)
    LCD_WriteData(*text++);
}

//
// Go to line, column
//

void LCD_GoTo(uint8_t x, uint8_t y) {
  LCD_WriteCommand(HD44780_DDRAM_SET | (x + (0x40 * y)));
}

//
// Clear display function
//

void LCD_Clear(void) {
  LCD_WriteCommand(HD44780_CLEAR);
  HAL_Delay(2);
}

//
// Go to first line/column
//

void LCD_Home(void) {
  LCD_WriteCommand(HD44780_HOME);
  HAL_Delay(2);
}

//
// Inicjalization function
//

void LCD_Initalize(void) {

  HAL_Delay(15);
  LCD_RS_GPIO_Port->BRR = LCD_RS_Pin;
  LCD_E_GPIO_Port->BRR = LCD_E_Pin;

  uint8_t i = 3;
  while (i--) // Initialization loop
  {
    LCD_E_GPIO_Port->BSRR = LCD_E_Pin;
    _LCD_OutNibble(0x03); // 8-bit mode
    LCD_E_GPIO_Port->BRR = LCD_E_Pin;
    HAL_Delay(5);
  }

  LCD_E_GPIO_Port->BSRR = LCD_E_Pin;
  _LCD_OutNibble(0x02); // 4-bit mode
  LCD_E_GPIO_Port->BRR = LCD_E_Pin;
  HAL_Delay(1);
  LCD_WriteCommand(HD44780_FUNCTION_SET | HD44780_FONT5x7 | HD44780_TWO_LINE | HD44780_4_BIT);
  LCD_WriteCommand(HD44780_DISPLAY_ONOFF | HD44780_DISPLAY_OFF);
  LCD_WriteCommand(HD44780_CLEAR);
  HAL_Delay(2);
  LCD_WriteCommand(HD44780_ENTRY_MODE | HD44780_EM_SHIFT_CURSOR | HD44780_EM_INCREMENT);
  LCD_WriteCommand(HD44780_DISPLAY_ONOFF | HD44780_DISPLAY_ON | HD44780_CURSOR_OFF | HD44780_CURSOR_NOBLINK);
}

//
//	End of file
//