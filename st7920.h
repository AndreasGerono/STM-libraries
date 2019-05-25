// ST7920 library with 4-bit transmission mode
// PSB pin for parallel communication HI !!

#include "stdint.h"

//
// Configurate GPIO with CubeMx
//

//	LCD_DB7
//	LCD_DB6
//	LCD_DB5
//	LCD_DB4
//	LCD_RS
//	LCD_E

//
// ST7920 instruction set
//

#define ST7920_CLEAR 0x01

#define ST7920_HOME 0x02

#define ST7920_ENTRY_MODE 0x04
#define ST7920_EM_SHIFT_CURSOR 0
#define ST7920_EM_SHIFT_DISPLAY 1
#define ST7920_EM_DECREMENT 0
#define ST7920_EM_INCREMENT 2

#define ST7920_DISPLAY_ONOFF 0x08
#define ST7920_DISPLAY_OFF 0
#define ST7920_DISPLAY_ON 4
#define ST7920_CURSOR_OFF 0
#define ST7920_CURSOR_ON 2
#define ST7920_CURSOR_NOBLINK 0
#define ST7920_CURSOR_BLINK 1

#define ST7920_DISPLAY_CURSOR_SHIFT 0x10
#define ST7920_SHIFT_CURSOR 0
#define ST7920_SHIFT_DISPLAY 8
#define ST7920_SHIFT_LEFT 0
#define ST7920_SHIFT_RIGHT 4

#define ST7920_FUNCTION_SET 0x20
#define ST7920_FONT5x7 0
#define ST7920_FONT5x10 4
#define ST7920_ONE_LINE 0
#define ST7920_TWO_LINE 8
#define ST7920_4_BIT 0
#define ST7920_8_BIT 16


//
// ST7920 function declaration
//

void LCD_GraphicMode();
void LCD_WriteCommand(uint8_t);
void LCD_WriteData(uint8_t);
void LCD_WriteText(char *);
void LCD_GoTo(uint8_t, uint8_t);
void LCD_Clear(void);
void LCD_Home(void);
void LCD_Initalize(void);

//
// End of file
//