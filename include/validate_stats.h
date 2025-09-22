#ifndef VALIDATE_STATS_H
#define VALIDATE_STATS_H

#include <stdbool.h>
#include "player.h"

//Function to validate match
bool validate_match(player *pl,int value);

//Function to validate fouls.
bool validate_foul(player *pl,int value);

//Function to validate made, attempted shots
bool validate_shots(player *pl,int stat,int value);

//Function to validate rebounds
bool validate_rebs(player *pl,int stat,int value,int *total,int *off,int *def);

//Function to check made-attempted
bool check_pt(int made,int attempted);

//Function to check that all the stats are positive
bool check_negative(int val);

//Function to check that all the stats are zero or not
bool check_not_zero(int *array,int numsSize);

#endif