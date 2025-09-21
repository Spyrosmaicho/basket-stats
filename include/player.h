#ifndef PLAYER_H
#define PLAYER_H

typedef struct player player;
#include <stdio.h>

//Compare functions 
int cmp_points(const void *a,const void *b);
int cmp_rebs(const void *a,const void *b);
int cmp_ass(const void *a,const void *b);
int cmp_steals(const void *a,const void *b);
int cmp_blocks(const void *a,const void *b);
int cmp_tos(const void *a,const void *b);
int cmp_matches(const void *a,const void *b);
int cmp_two_percent(const void *a,const void *b);
int cmp_three_percent(const void *a,const void *b);
int cmp_ft_percent(const void *a,const void *b);

//Function to create a player
player *create_player(char *name);

//Function to deallocate the memory for a player
void delete_player(void *item);

//Function to check if an element is in an item
int check_player(void *item,void *elem);

//Function to insert stats into a player
player *insert_player_stats(player *pl,int *array_of_stats);

//Helper function to print a player
void print_player(player *pl,FILE *file,int len);

//Function to return the length of the name of a player
int player_name_len(void *data);

/*GET FUNCTIONS*/
char *get_name(player *person);
int get_points(player *person);
int get_rebounds(player *person);
int get_assists(player *person);
int get_steals(player *person);
int get_blocks(player *person);
int get_matches(player *person);
int get_tos(player *person);
int get_two_made(player *person);
int get_two_attempted(player *person);
int get_three_made(player *person);
int get_three_attempted(player *person);
int get_ft_made(player *person);
int get_ft_attempted(player *person);
double get_2p_percentage(player *person);
double get_3p_percentage(player *person);
double get_1p_percentage(player *person);

/*ADD FUNCTIONS*/
void add_points(player *new,int points);
void add_rebs(player *new,int rebs);
void add_ass(player *new,int ass);
void add_steals(player *new,int steals);
void add_blocks(player *new,int blocks);
void add_tos(player *new,int tos);
void add_matches(player *new,int matches);
void add_1p_made(player *new,int tp);
void add_1p_attempted(player *new,int tp);
void add_2p_made(player *new,int tp);
void add_2p_attempted(player *new,int tp);
void add_3p_made(player *new,int tp);
void add_3p_attempted(player *new,int tp);
void add_2p_percent(player *new);
void add_3p_percent(player *new);
void add_1p_percent(player *new);

#endif