#ifndef PLAYER_OP_H
#define PLAYER_OP_H

#include <stdbool.h>
#include "vector.h"
#include "hashtable.h"
#include "player.h"
#include "team.h"

extern const char *fields[];

//Function to remove a player from the list of the team
bool remove_player(hashtable **ht,vector **vec,team *t);

//Function to read a new player and add him to the list of the team
bool read_player(hashtable **ht,vector **vect);

//Function to print an object of a player to a json file
void print_player_object(player *pl,FILE *file_json);

#endif