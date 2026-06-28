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

bool remove_player_pipe(hashtable **ht,vector **vec,team *t,char *name);

//Function to read a new player and add him to the list of the team
bool read_player(hashtable **ht,vector **vect);

//Function to read a player using cmd line args
void add_player(hashtable **ht,vector **vec,char *name);

//Function to print an object of a player to a json file
void print_player_object(player *pl,FILE *file_json);

//Function to print a player to a csv file
void print_player_csv(player *pl,FILE *f);

//Function to add stats to a SQL database
void save_to_sql(vector *vec);

#endif