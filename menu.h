//
// Menu library
//

#include "stdint.h"
#include "st7920.h"

//
//Define navigaton inputs in CubeMx as external interrupt
//
//BTN_UP_Pin
//BTN_OK_Pin
//BTN_DOWN_Pin

#define SELECTION 0x07
#define NEXT ' '
#define LCD_ROWS  4 //number of rows in display
#define LCD_COLUMNS 16 //number of columns in display

typedef void (*menuitemfuncptr)(); //pointer to menu click function (new pointer type)


struct _menuitem {  
  char *text;
  menuitemfuncptr menuitemfunc; //menu click function
  struct _menuitem *parent; //first element of every menu
  struct _menuitem *submenu;  
  struct _menuitem *next; //Menu below, if 0 last Menuitem
};


void Menu_Show();
void Menu_SelectNext();
void Menu_SelectPrev();
void Menu_Click();
void Menu_Back();


extern struct _menuitem menu; //new menu struct (forward declaration)
extern struct _menuitem menuUpdate; //empty menu to update names  (forward declaration)