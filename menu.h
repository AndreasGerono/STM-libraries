//
// menu.h
// Created by Andreas Gerono on 11/07/2019.

//
//New library for menu
//To do: add display support

#ifndef _menu_h_
#define _menu_h_

typedef struct MenuItem* MenuItemPtr;
typedef struct MenuItem MenuItem;

struct MenuItem{
    char* name;
    MenuItemPtr next;
    MenuItemPtr prev;
    MenuItemPtr up;
    MenuItemPtr down;
};


void menu_draw();
void menu_next();
void menu_prev();
void menu_ok();
void print_current();
MenuItem new_menuItem(char* name, MenuItemPtr next, MenuItemPtr prev, MenuItemPtr up, MenuItemPtr down);



#endif