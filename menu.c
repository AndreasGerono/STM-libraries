//
// menu.c
// Created by Andreas Gerono on 14/07/2019.

#include "menu.h"
#include <stdlib.h>
#include <stdio.h>

#define ROWS 3



int main(){
    Menu_ptr menu1 = menu_new(4);
    Menu_ptr menu11 = menu_new(2);
    Menu_ptr menu111 = menu_new(2);
    
    menu_add_item(menu1, "menu1", NULL);
    menu_add_item(menu1, "menu2", NULL);
    menu_add_item(menu1, "menu3", menu11);
    menu_add_item(menu1, "menu4", NULL);
    
    menu_add_item(menu11, "menu11", menu111);
    menu_add_item(menu11, "menu12", menu1);
    
    menu_add_item(menu111, "menu111", menu11);
    menu_add_item(menu111, "menu112", NULL);
    
    
    char key = '0';
    menu_draw();
    while (key != 'e') {
        scanf("%c", &key);
        if (key == '1') 
            menu_previous();
        if (key == '2') 
            menu_ok();
        if (key == '3') 
            menu_next();
        if (key == '4')
            menu_current();
    }
}

Menu_ptr currentMenu = NULL;


struct Menu_item{
    char* name;
    Menu_ptr next;
};

struct Menu{
    struct Menu_item *list;    
    int8_t index;
    int8_t items;
    int8_t position;
    int8_t top;
};


Menu_ptr menu_new(size_t size){
    Menu_ptr menu = malloc( sizeof * menu);
    menu->list = malloc(size * sizeof(struct Menu));
    menu->index = 0;
    menu->items = 0;
    menu->position = 0;
    menu->top = 0;
    if (NULL == currentMenu) {
        currentMenu = menu;
    }
    return menu;
}

static struct Menu_item new_item(char* name, Menu_ptr next){
    struct Menu_item item;
    item.name = name;
    item.next = next;
    return item;
}

void menu_add_item(Menu_ptr menu, char* name, Menu_ptr next){
    struct Menu_item item = new_item(name, next);
    menu->list[menu->items] = item;
    menu->items++;
}

void menu_current(){
    char* name = currentMenu->list[currentMenu->index].name;
    printf("%s %d %d %d\n", name, currentMenu->position, currentMenu->top, currentMenu->index);
}


void menu_next(){
    if (currentMenu->index < currentMenu->items-1) {
        ++currentMenu->index;
        ++currentMenu->position;
        if (currentMenu->position >= ROWS) {
            currentMenu->position = ROWS-1;
            ++currentMenu->top;
        }
        menu_draw();
    }
    else {
        printf("Brak!\n");
    }      
}

void menu_previous(){
    if (currentMenu->index > 0) {
        --currentMenu->index;
        --currentMenu->position;
         if (currentMenu->position < 0) {
                currentMenu->position = 0;
                --currentMenu->top;
            }
        menu_draw();
    }
    else {
        printf("Brak!\n");
    }    
}

void menu_ok(){
    if (NULL != currentMenu->list[currentMenu->index].next) {
        currentMenu = currentMenu->list[currentMenu->index].next;
        menu_draw();
    }
    else {
        printf("Brak!\n");
    }
}


static void draw_item(int8_t index){
    printf( "%s", currentMenu->list[index].name);
    if (index == currentMenu->index) {
        printf("  <--");
    }
    printf("\n");
}


void menu_draw(){
    system("clear");
    for (int8_t i = currentMenu->top; i < ROWS+currentMenu->top; i++) {
        if (i >= currentMenu->items) {
            break;
        }
        draw_item(i);
    }
    printf("\nend\n\n");
}