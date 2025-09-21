#ifndef MENU_H
#define MENU_H

#include "hashtable.h"
#include "vector.h"

void show_main_menu(void);
void show_new_data_menu(void);
void show_top_menu(void);
void error_handler(hashtable *ht,vector *vec);

#endif