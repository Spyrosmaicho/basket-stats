#include <stdlib.h>
#include "player.h"
#include <string.h>

struct player{
    char *name; 
    int points;
    int rebs;
    int ass;
    int steals;
    int blocks;
    int tos;
    int matches;
};

//Useful for comparisons in bst
int player_cmp(const void *a, const void *b) 
{
    const char *pa = a;
    const player *pb = (const player *)b;
    return strcmp(pa, pb->name);
}

//Function to copy a value in a node of bst
char *copy(player *person,char *val)
{
    person->name = strdup(val);
    if(!person->name) return NULL;
    return person->name;
}

void free_val(void *ptr)
{
    player *p = ptr;

    if(p)
    {
        free(p->name);
        free(p);
    }
}


//Function to get the name of the player
char *get_name(player *person)
{
    return person->name;
}

//Function to return the points of a player
int get_points(player *person)
{
    return person->points;
}


//Function to return the rebounds of a player
int get_rebounds(player *person)
{
    return person->rebs;
}

//Function to return the assists of a player
int get_assists(player *person)
{
    return person->ass;
}

//Function to return the steals of a player
int get_steals(player *person)
{
    return person->steals;
}

//Function to return the blocks of a player
int get_blocks(player *person)
{
    return person->blocks;
}

//Function to return the matches of a player
int get_matches(player *person)
{
    return person->matches;
}

//Function to get the turnovers of a player
int get_tos(player *person)
{
    return person->tos;
}

//Helper function to return the sizeof(player)
int get_sizeof_player()
{
    return sizeof(player);
}

//Function to add points
void add_points(int points,player *new)
{
    new->points +=points;
}

//Function to add rebounds
void add_rebs(int rebs,player *new)
{
    new->rebs +=rebs;
}

//Function to add assists
void add_ass(int ass,player *new)
{
    new->ass +=ass;
}

//Function to add steals
void add_steals(int steals,player *new)
{
    new->steals +=steals;
}

//Function to add blocks
void add_blocks(int blocks,player *new)
{
    new->blocks +=blocks;
}

//Function to add tos
void add_tos(int tos,player *new)
{
    new->tos +=tos;
}

//Function to add matches
void add_matches(int matches,player *new)
{
    new->matches +=matches;
}