#ifndef IO_H
#define IO_H

#include <stdio.h>
#include "hashtable.h"
#include "vector.h"
#include "team.h"

//print player header
void print_player_header(int len,FILE *file);
//print team header
void print_team_header(FILE *file);

//Function to use getline
char *get_line(void);

//Helper function to clear stdin in order to make getline work properly
void clear_stdin(void) ;

//Functions to handle errors and print error messages 
void error_handler(hashtable *ht,vector *vec,team *t);
void error_message(char *mes);

//For printing purposes
void line(void);

//Function to print stats of a specific player
void print_one_player(hashtable *ht);

//Function to print stats of all players
void print_all_players(vector *vec,char *filename);

//Function to print the top 3 players according to user's choice
void print_top_players(vector *vec, int stat) ;

//Function to print the stats of the team
void print_team_stats(vector *vec,team *t,char *filename);

#endif