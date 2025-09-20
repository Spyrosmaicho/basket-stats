#ifndef BASKET_H
#define BASKET_H

#include <stdbool.h>
#include "vector.h"
#include "hashtable.h"

//Function to use getline
char *get_line(void);

//Function to print stats of all players of the team
void print_all_players(vector *vec,char *filename);

//Function to print stats of a specific player
void print_one_player(hashtable *ht);

//Function to add stats of a player
void add_stats(hashtable *ht);

//Function to remove a player from the list of the team
bool remove_player(hashtable **ht,vector **vec);

//Function to read a new player and add him to the list of the team
bool read_player(hashtable **ht,vector **vect);

//Function to print the top 3 players according to user's choice
void print_top_players(vector *vec,int stat);

//For printing purposes
void line(void);

//Helper function to clear stdin in order to make getline work properly
void clear_stdin(void);

//Function to get the file with the players 
bool load_file(hashtable **ht,vector **vec);

#endif