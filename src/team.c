#include <stdlib.h>
#include "team.h"

/*Hidden struct from user*/
struct team
{
    int points;
    int total_rebs;
    int off_rebs;
    int def_rebs;
    int ass;
    int steals;
    int blocks;
    int tos;
    int fouls;
    int matches;
    int two_point_made;
    int two_point_attempted;
    int three_point_made;
    int three_point_attempted;
    int ft_made;
    int ft_attempted;
};

//Function to create a team
team *create_team(void)
{
    team * t = calloc(1,sizeof(team));
    if(!t) return NULL;

    return t;
}

//Function to deallocate all memory for a team
void destroy_team(team *t)
{
    if(t) free(t);
}

void set_team_matches(team *t,int matches){t->matches = matches;}

//Helper function to print a team
void print_team(team *t,FILE *file)
{
    int points = get_team_points(t);
    int rebs = get_team_rebs(t);
    int off = get_team_off(t);
    int def = get_team_def(t);
    int ass = get_team_ass(t);
    int steals = get_team_steals(t);
    int blocks = get_team_blocks(t);
    int tos = get_team_tos(t);
    int fouls = get_team_fouls(t);
    int matches = t->matches;
    int two_made = t->two_point_made;
    int two_attempted = t->two_point_attempted;
    int three_made = t->three_point_made;
    int three_attempted = t->three_point_attempted;
    int ft_made = t->ft_made;
    int ft_attempted = t->ft_attempted;
    double one_percent = 0.0;
    if(ft_attempted != 0) one_percent = t->ft_made*100 / t->ft_attempted;
    double two_percent = 0.0;
    if(two_attempted !=0) two_percent = t->two_point_made*100 / t->two_point_attempted;
    double three_percent = 0.0;
    if(three_attempted!= 0) three_percent = t->three_point_made*100 / t->three_point_attempted;
   if(!file)printf("%-7d | %8d (%d - %d) | %7d | %6d | %6d | %5d | %5d | %7d | %4d / %-4d | %4d / %-4d | %4d / %-4d | %6.2f | %6.2f | %6.2f\n",
    points,rebs,off,def,ass,steals,blocks,tos,fouls,matches,ft_made,ft_attempted,two_made,two_attempted,three_made,three_attempted,one_percent,two_percent,three_percent);
   else fprintf(file,"%-7d | %8d (%d - %d) | %7d | %6d | %6d | %5d | %5d | %7d | %4d / %-4d | %4d / %-4d | %4d / %-4d | %6.2f | %6.2f | %6.2f\n",
    points,rebs,off,def,ass,steals,blocks,tos,fouls,matches,ft_made,ft_attempted,two_made,two_attempted,three_made,three_attempted,one_percent,two_percent,three_percent);
}


    /*GET FUNCTIONS*/
int get_team_points(team *t){return t->points;}
int get_team_rebs(team *t){return t->total_rebs;}
int get_team_def(team *t){return t->def_rebs;}
int get_team_off(team *t){return t->off_rebs;}
int get_team_ass(team *t){return t->ass;}
int get_team_steals(team *t){return t->steals;}
int get_team_blocks(team *t){return t->blocks;}
int get_team_tos(team *t){return t->tos;}
int get_team_fouls(team *t){return t->fouls;}
int get_team_matches(team *t){return t->matches;}
int get_team_mft(team *t){return t->ft_made;}
int get_team_aft(team *t){return t->ft_attempted;}
int get_team_mtwo(team *t){return t->two_point_made;}
int get_team_atwo(team *t){return t->two_point_attempted;}
int get_team_mthree(team *t){return t->three_point_made;}
int get_team_athree(team *t){return t->three_point_attempted;}

    /*ADD FUNCTIONS*/
void add_team_points(team *t,int points){t->points+=points;}
void add_team_rebs(team *t,int rebs){t->total_rebs+=rebs;}
void add_team_def(team *t,int def){t->def_rebs+=def;}
void add_team_off(team *t,int off){t->off_rebs+=off;}
void add_team_ass(team *t,int ass){t->ass += ass;}
void add_team_steals(team *t,int steals){t->steals +=steals;}
void add_team_blocks(team *t,int blocks){t->blocks +=blocks;}
void add_team_tos(team *t,int tos){t->tos += tos;}
void add_team_fouls(team *t,int fouls){t->fouls += fouls;}
void add_team_mft(team *t,int made){t->ft_made+=made;}
void add_team_aft(team *t,int attempted){t->ft_attempted+=attempted;}
void add_team_mtwo(team *t,int made){t->two_point_made+=made;}
void add_team_atwo(team *t,int attempted){t->two_point_attempted+=attempted;}
void add_team_mthree(team *t,int made){t->three_point_made+=made;}
void add_team_athree(team *t,int attempted){t->three_point_attempted+=attempted;}


    /*REMOVE FUNCTIONS*/
void rem_team_points(team *t,int points){t->points -= points;}
void rem_team_rebs(team *t,int rebs){t->total_rebs-=rebs;}
void rem_team_def(team *t,int def){t->def_rebs-=def;}
void rem_team_off(team *t,int off){t->off_rebs-=off;}
void rem_team_ass(team *t,int ass){t->ass -= ass;}
void rem_team_steals(team *t,int steals){t->steals -=steals;}
void rem_team_blocks(team *t,int blocks){t->blocks -=blocks;}
void rem_team_tos(team *t,int tos){t->tos -= tos;}
void rem_team_fouls(team *t,int fouls){t->fouls -= fouls;}
void rem_team_match(team *t,int matches){t->matches -= matches;}
void rem_team_mft(team *t,int made){t->ft_made-=made;}
void rem_team_aft(team *t,int attempted){t->ft_attempted-=attempted;}
void rem_team_mtwo(team *t,int made){t->two_point_made-=made;}
void rem_team_atwo(team *t,int attempted){t->two_point_attempted-=attempted;}
void rem_team_mthree(team *t,int made){t->three_point_made-=made;}
void rem_team_athree(team *t,int attempted){t->three_point_attempted-=attempted;}