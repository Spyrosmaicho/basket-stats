#ifndef PLAYER_H
#define PLAYER_H

typedef struct player player;

//Useful for comparisons in bst
int player_cmp(const void *a, const void *b);

//Function to get the name of the player
char *get_name(player *person);

//Function to return the points of a player
int get_points(player *person);

//Function to return the rebounds of a player
int get_rebounds(player *person);

//Function to return the assists of a player
int get_assists(player *person);

//Function to return the steals of a player
int get_steals(player *person);

//Function to return the blocks of a player
int get_blocks(player *person);

//Function to return the matches of a player
int get_matches(player *person);

//Function to get the turnovers of a player
int get_tos(player *person);

//Function to free a player
void free_val(void *ptr);

//Helper function to return the sizeof(player)
int get_sizeof_player(void);

//Function to add points
void add_points(int points,player *new);

//Function to add rebounds
void add_rebs(int rebs,player *new);

//Function to add assists
void add_ass(int ass,player *new);

//Function to add steals
void add_steals(int steals,player *new);

//Function to add blocks
void add_blocks(int blocks,player *new);

//Function to add tos
void add_tos(int tos,player *new);

//Function to add matches
void add_matches(int matches,player *new);

//Function to copy a value in a node of bst
char *copy(player *person,char *val);

#endif