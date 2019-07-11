//
// menu.c
// Created by Andreas Gerono on 11/07/2019.

#include "menu.h"
#include <stdlib.h>
#include <stdio.h>

#define ROWS 2


MenuItemPtr current_menu = NULL;
MenuItemPtr top_menu = NULL;
uint8_t position = 0;

static void menuItem_print(MenuItemPtr menu){    //
    if (NULL != menu->name) {
        printf("%s", menu->name);
        if (menu->name == current_menu->name) {
            printf("    <--");
        }
        printf("\n");
    }
}

void menu_draw(){
    system("clear");
    MenuItemPtr instance = top_menu;
    for (int i = 0; i < ROWS; ++i) {
        if (NULL != instance) {
            menuItem_print(instance);
            instance = instance->next;
        }
        else {
            break;
        }
    }
    printf("End\n\n");
}



void menu_next(){
    if (NULL != current_menu->next) {
        current_menu = current_menu->next;
        ++position;
        if (position >= ROWS){
            position = ROWS;
            top_menu = top_menu->next;
        }
    menu_draw();
    }
}

void menu_prev(){
    if (NULL != current_menu->prev) {
        current_menu = current_menu->prev;
        --position;
        if (position == 0) {
            top_menu = top_menu->prev;
            position = 0;
        }
    menu_draw();
    }
}

void menu_ok(){
    if (NULL != current_menu->up) {
        current_menu = current_menu->up;
        top_menu = current_menu;
        position = 0;
        menu_draw();
    }
    else if (NULL != current_menu->down) {
        current_menu = current_menu->down;
        top_menu = current_menu;
        position = 0;
        menu_draw();
    }
    else {
        printf("Brak!\n");
    }
}


MenuItem new_menuItem(char* name, MenuItemPtr next, MenuItemPtr prev, MenuItemPtr up, MenuItemPtr down){
    MenuItem instance;
    instance.name = name;
    instance.next = next;
    instance.prev = prev;
    instance.up = up;
    instance.down = down;
    
    if (NULL == current_menu) {
        current_menu = &instance;
        top_menu = current_menu;
    }
    return instance;
}