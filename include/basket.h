#ifndef BASKET_H
#define BASKET_H

#include <stdbool.h>
#include "avl.h"

//Function to use getline
char *get_func(void);

//Function to print stats of all players
void print_team(avl *avl,char *filename);

//Function to print stats of a specific player
void print_stats(avl *avl);

//Function to add stats of a player
void add_stats(avl *avl);

//Function to remove a player from the list of the team
bool rem(avl **avl);

//Function to read a new player and add him to the list of the team
bool read_player(avl **avl);

//For printing purposes
void line(void);

//Helper function to clear stdin in order to make getline work properly
void clear_stdin(void);

//Function to get the file with the players 
avl *load_file(avl *avl);

#endif