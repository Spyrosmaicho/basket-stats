#include <stdlib.h>
#include <string.h>
#include "player.h"

struct player{
    char *name; 
    int points;
    int rebs;
    int ass;
    int steals;
    int blocks;
    int tos;
    int matches;
    int two_point_made;
    int two_point_attempted;
    int three_point_made;
    int three_point_attempted;
    int ft_made;
    int ft_attempted;
    double ft_percent;
    double two_percent;
    double three_percent;
};

int cmp_points(const void *a,const void *b)
{
    player *pa = *(player **)a;
    player *pb = *(player**)b;
    
     return pb->points - pa->points;
}
int cmp_rebs(const void *a,const void *b)
{
    player *pa = *(player **)a;
    player *pb = *(player**)b;
    
    return pb->rebs - pa->rebs;
}
int cmp_ass(const void *a,const void *b)
{
    player *pa = *(player **)a;
    player *pb = *(player**)b;
    
    return pb->ass - pa->ass;
}
int cmp_steals(const void *a,const void *b)
{
    player *pa = *(player **)a;
    player *pb = *(player**)b;
    
    return pb->steals - pa->steals;
}
int cmp_blocks(const void *a,const void *b)
{
    player *pa = *(player **)a;
    player *pb = *(player**)b;
    
    return pb->blocks - pa->blocks;
}
int cmp_tos(const void *a,const void *b)
{
    player *pa = *(player **)a;
    player *pb = *(player**)b;
    
    return pb->tos - pa->tos;
}
int cmp_matches(const void *a,const void *b)
{
    player *pa = *(player **)a;
    player *pb = *(player**)b;
    
    return pb->matches - pa->matches;
}
int cmp_two_percent(const void *a,const void *b)
{
    player *pa = *(player **)a;
    player *pb = *(player**)b;
    
    if (pb->two_percent > pa->two_percent) return 1;
    if (pb->two_percent < pa->two_percent) return -1;
    return 0;
}
int cmp_three_percent(const void *a,const void *b)
{
    player *pa = *(player **)a;
    player *pb = *(player**)b;
    
    if (pb->three_percent > pa->three_percent) return 1;
    if (pb->three_percent < pa->three_percent) return -1;
    return 0;
}
int cmp_ft_percent(const void *a,const void *b)
{
    player *pa = *(player **)a;
    player *pb = *(player**)b;
    
    if (pb->ft_percent > pa->ft_percent) return 1;
    if (pb->ft_percent < pa->ft_percent) return -1;
    return 0;
}
//Function that creates a player
player *create_player(char *name)
{
    player *pl = calloc(1,sizeof(player));
    if(!pl) return NULL;
    pl->name = strdup(name);
    if(!pl->name) 
    {
        free(pl);
        return NULL;
    }
    return pl;
}

//Function to deallocate the memory for a player
void delete_player(void *item)
{
    player *pl = item;
    free(pl->name);
    free(pl);
}

    /*FUNCTIONS FOR GET*/
//Function to get the name of the player
char *get_name(player *person){return person->name;}
int get_points(player *person){return person->points;}
int get_rebounds(player *person){return person->rebs;}
int get_assists(player *person){return person->ass;}
int get_steals(player *person){return person->steals;}
int get_blocks(player *person){return person->blocks;}
int get_matches(player *person){return person->matches;}
int get_tos(player *person){return person->tos;}
int get_two_made(player *person){return person->two_point_made;}
int get_two_attempted(player *person){return person->two_point_attempted;}
int get_three_made(player *person){return person->three_point_made;} 
int get_three_attempted(player *person){return person->three_point_attempted;}
int get_ft_made(player *person){return person->ft_made;}
int get_ft_attempted(player *person){return person->ft_attempted;}
double get_2p_percentage(player *person){return person->two_point_made*100.0 / person->two_point_attempted;}
double get_3p_percentage(player *person){return person->three_point_made*100.0 / person->three_point_attempted;}
double get_1p_percentage(player *person){return person->ft_made *100.0 / person->ft_attempted;}

    /*FUNCTIONS FOR ADD*/
void add_points(player *new,int points){new->points +=points;}
void add_rebs(player *new,int rebs){new->rebs +=rebs;}
void add_ass(player *new,int ass){new->ass +=ass;}
void add_steals(player *new,int steals){new->steals +=steals;}
void add_blocks(player *new,int blocks){new->blocks +=blocks;}
void add_tos(player *new,int tos){new->tos +=tos;}
void add_matches(player *new,int matches){new->matches +=matches;}
void add_2p_made(player *new,int tp){new->two_point_made += tp;new->points+=2*tp;}
void add_2p_attempted(player *new,int tp){new->two_point_attempted += tp;}
void add_3p_made(player *new,int tp){new->three_point_made += tp;new->points+=3*tp;}
void add_3p_attempted(player *new,int tp){new->three_point_attempted += tp;}
void add_1p_made(player *new,int tp){new->ft_made+=tp;new->points +=tp;}
void add_1p_attempted(player *new,int tp){new->ft_attempted+=tp;}
void add_2p_percent(player *new){new->two_percent = get_2p_percentage(new);}
void add_3p_percent(player *new){new->three_percent = get_3p_percentage(new);}
void add_1p_percent(player *new){new->ft_percent = get_1p_percentage(new);}

//Helper function to print a player
void print_player(player *pl,FILE *file,int len)
{
    char *name = get_name(pl);
    int points = get_points(pl);
    int rebs = get_rebounds(pl);
    int ass = get_assists(pl);
    int steals = get_steals(pl);
    int blocks = get_blocks(pl);
    int tos = get_tos(pl);
    int matches = get_matches(pl);
    int two_made = pl->two_point_made;
    int two_attempted = pl->two_point_attempted;
    int three_made = pl->three_point_made;
    int three_attempted = pl->three_point_attempted;
    int ft_made = get_ft_made(pl);
    int ft_attempted = get_ft_attempted(pl);
    double one_percent = 0.0;
    if(ft_attempted != 0) one_percent = get_1p_percentage(pl);
    double two_percent = 0.0;
    if(two_attempted !=0) two_percent = get_2p_percentage(pl);
    double three_percent = 0.0;
    if(three_attempted!= 0) three_percent = get_3p_percentage(pl);
   printf("%-*s | %7d | %8d | %7d | %6d | %6d | %5d | %7d | %4d / %-4d | %4d / %-4d | %4d / %-4d | %6.2f | %6.2f | %6.2f\n",len,
    name,points,rebs,ass,steals,blocks,tos,matches,ft_made,ft_attempted,two_made,two_attempted,three_made,three_attempted,one_percent,two_percent,three_percent);
   if(file) fprintf(file,"%-*s | %7d | %8d | %7d | %6d | %6d | %5d | %7d | %4d / %-4d | %4d / %-4d | %4d / %-4d | %6.2f | %6.2f | %6.2f\n",len,
    name,points,rebs,ass,steals,blocks,tos,matches,ft_made,ft_attempted,two_made,two_attempted,three_made,three_attempted,one_percent,two_percent,three_percent);
}

player *insert_player_stats(player *pl,int *array_of_stats)
{
    add_1p_made(pl,array_of_stats[0]);
    add_2p_made(pl,array_of_stats[1]);
    add_3p_made(pl,array_of_stats[2]);
    add_1p_attempted(pl,array_of_stats[3]);
    add_2p_attempted(pl,array_of_stats[4]);
    add_3p_attempted(pl,array_of_stats[5]);
    add_rebs(pl,array_of_stats[6]);
    add_ass(pl,array_of_stats[7]);
    add_steals(pl,array_of_stats[8]);
    add_blocks(pl,array_of_stats[9]);
    add_tos(pl,array_of_stats[10]);
    add_matches(pl,array_of_stats[11]);
    
    add_2p_percent(pl);
    add_3p_percent(pl);
    add_1p_percent(pl);
    return pl;
}

int check_player(void *item,void *elem)
{
    player *pl = item;
    char *name = elem;
    return  strcasecmp(pl->name, name) == 0;
}

int player_name_len(void *data)
{
    player *pl = data;
    return strlen(pl->name);
}