#ifndef PLAYER_OP_H
#define PLAYER_OP_H

#include <stdbool.h>
#include "vector.h"
#include "hashtable.h"
#include "player.h"
#include "team.h"

//Function to add stats of a player
void add_stats(hashtable *ht,team *t);

//Helper function to add the stats of a player into the team stats
void add_player_stats(team *t,player *pl);

//Helper function to remove the stats of a player from the team stats
void remove_player_stats(team *t,player *pl);

//Function to remove a player from the list of the team
bool remove_player(hashtable **ht,vector **vec,team *t);

//Function to read a new player and add him to the list of the team
bool read_player(hashtable **ht,vector **vect);

#endif