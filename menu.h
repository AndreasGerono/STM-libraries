//
// menu.h
// Created by Andreas Gerono on 14/07/2019.

#ifndef _menu_h_
#define _menu_h_
#include <stdio.h>

typedef struct Menu* Menu_ptr;

Menu_ptr menu_new(size_t size);
void menu_current();
void menu_next();
void menu_previous();
void menu_ok();
void menu_draw();

void menu_add_item(Menu_ptr menu, char* name, Menu_ptr next);


#endif