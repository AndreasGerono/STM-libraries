#include "menu.h"
#include "st7920.h"


//Version without rotating/rolling mode

static struct _menuitem *currMenuPtr = &menu; //Pointer to current selected Menu item (current drawed)
static int8_t menuindex;                      //Selected menu
static int8_t menufirstpos;                   //Menu on top

static void Menu_UpdateNames() {
  menuUpdate.menuitemfunc();
}

static uint8_t Menu_GetMenuItemsNo() //counts menu items (from one parent)
{
  struct _menuitem *tmpmenuitem = currMenuPtr;
  uint8_t index = 0;
  while (tmpmenuitem) {
    tmpmenuitem = tmpmenuitem->next;
    index++;
  }
  return index;
}

static struct _menuitem *Menu_GetMenuItem(uint8_t index) { //
  struct _menuitem *tmpmenuitem = currMenuPtr;

  while ((tmpmenuitem) && (index > 0)) {
    tmpmenuitem = tmpmenuitem->next;
    index--;
  }
  return tmpmenuitem;
}

static uint8_t Menu_GetMenuRows() { //Maximum menu elements on LCD
  return LCD_ROWS;
}

void Menu_Show() {
  Menu_UpdateNames();
  struct _menuitem *tmpmenuitem = Menu_GetMenuItem(menufirstpos);
  uint8_t menuitemsno = Menu_GetMenuItemsNo();
  LCD_Clear(); //

  for (uint8_t i = 0; i < Menu_GetMenuRows(); i++) {
    LCD_GoTo(0, i);                        //
    if (menuindex == ((menufirstpos + i))) //
      LCD_WriteData(SELECTION);
    else
      LCD_WriteData(' ');             //
    LCD_WriteText(tmpmenuitem->text); //
    if (tmpmenuitem->submenu)
      LCD_WriteData(NEXT); //
    tmpmenuitem = tmpmenuitem->next;
    if (tmpmenuitem == NULL) //
      break;                 //
  }
}

void Menu_SelectNext() {
  uint8_t no = Menu_GetMenuItemsNo();
  if (menuindex < no - 1) {
    menuindex++;
    if (no > Menu_GetMenuRows()) //check if menu number > LCD lines (to move down first position)
    {
      if (menuindex >= Menu_GetMenuRows()) //Move down menu when menu index > LCD lines
        menufirstpos++;
    }
    Menu_Show(); //
  }
}

void Menu_SelectPrev() {
  if (menuindex) {
    if (menuindex == menufirstpos)
      menufirstpos--;
    menuindex--; //
  }
  Menu_Show(); //
}

void Menu_Back() {
  menufirstpos = 0;
  menuindex = 0;
  currMenuPtr = currMenuPtr->parent;
}

void Menu_Click() {
  struct _menuitem *tmpmenuitem = Menu_GetMenuItem(menuindex);
  struct _menuitem *submenu = tmpmenuitem->submenu;
  menuitemfuncptr mfptr = tmpmenuitem->menuitemfunc;

  if (mfptr)
    (*mfptr)();
  if (submenu) {
    currMenuPtr = submenu;
    menuindex = 0;
    menufirstpos = 0;
  }
  Menu_Show();
}