#ifndef ADD_STATS_H
#define ADD_STATS_H

#include "hashtable.h"
#include "vector.h"
#include "team.h"
#include "player.h"

//Function to add stats of a player
void add_stats(hashtable *ht,vector *vec,team *t);

bool add_pipe(hashtable *ht, vector *vec, team *t, int stat, char *name, int value);

//Function to add simultaneously all the stats into a player
void add_all_player_stats(team *t,player *pl);

extern bool flag;

#endif