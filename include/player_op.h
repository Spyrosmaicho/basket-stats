#ifndef BASKET_H
#define BASKET_H

#include <stdbool.h>
#include "vector.h"
#include "hashtable.h"

//Function to add stats of a player
void add_stats(hashtable *ht);

//Function to remove a player from the list of the team
bool remove_player(hashtable **ht,vector **vec);

//Function to read a new player and add him to the list of the team
bool read_player(hashtable **ht,vector **vect);

//Function to get the file with the players 
bool load_file(hashtable **ht,vector **vec);

#endif