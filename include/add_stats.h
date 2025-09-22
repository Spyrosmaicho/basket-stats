#ifndef ADD_STATS_H
#define ADD_STATS_H

#include "hashtable.h"
#include "team.h"
#include "player.h"

//Function to add stats of a player
void add_stats(hashtable *ht,team *t);

//Function to add simultaneously all the stats into a player
void add_all_player_stats(team *t,player *pl);

#endif