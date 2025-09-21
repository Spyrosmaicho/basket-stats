#ifndef IO_H
#define IO_H

#include "hashtable.h"
#include "vector.h"

//print header
void print_header(int len);

//Function to use getline
char *get_line(void);

//Helper function to clear stdin in order to make getline work properly
void clear_stdin(void) ;

//For printing purposes
void line(void);

//Function to print stats of a specific player
void print_one_player(hashtable *ht);

//Function to print stats of all players
void print_all_players(vector *vec,char *filename);

//Function to print the top 3 players according to user's choice
void print_top_players(vector *vec, int stat) ;

#endif