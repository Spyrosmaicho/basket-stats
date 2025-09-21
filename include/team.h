#ifndef TEAM_H
#define TEAM_H

typedef struct team team;

#include <stdio.h>

//Function to create a team
team *create_team(void);

//Function to deallocate all memory for a team
void destroy_team(team *t);

//Helper function to print a team
void print_team(team *t,FILE *file);

//Function to set the matches of the team
void set_team_matches(team *t,int matches);

    /*GET FUNCTIONS*/
int get_team_points(team *t);
int get_team_rebs(team *t);
int get_team_def(team *t);
int get_team_off(team *t);
int get_team_ass(team *t);
int get_team_steals(team *t);
int get_team_blocks(team *t);
int get_team_tos(team *t);
int get_team_matches(team *t);
int get_team_mft(team *t);
int get_team_aft(team *t);
int get_team_mtwo(team *t);
int get_team_atwo(team *t);
int get_team_mthree(team *t);
int get_team_athree(team *t);

    /*ADD FUNCTIONS*/
void add_team_points(team *t,int points);
void add_team_rebs(team *t,int rebs);
void add_team_def(team *t,int def);
void add_team_off(team *t,int off);
void add_team_ass(team *t,int ass);
void add_team_steals(team *t,int steals);
void add_team_blocks(team *t,int blocks);
void add_team_tos(team *t,int tos);
void add_team_mft(team *t,int made);
void add_team_aft(team *t,int attempted);
void add_team_mtwo(team *t,int made);
void add_team_atwo(team *t,int attempted);
void add_team_mthree(team *t,int made);
void add_team_athree(team *t,int attempted);

    /*REMOVE FUNCTIONS*/
void rem_team_points(team *t,int points);
void rem_team_rebs(team *t,int rebs);
void rem_team_def(team *t,int def);
void rem_team_off(team *t,int off);
void rem_team_ass(team *t,int ass);
void rem_team_steals(team *t,int steals);
void rem_team_blocks(team *t,int blocks);
void rem_team_tos(team *t,int tos);
void rem_team_match(team *t,int matches);
void rem_team_mft(team *t,int made);
void rem_team_aft(team *t,int attempted);
void rem_team_mtwo(team *t,int made);
void rem_team_atwo(team *t,int attempted);
void rem_team_mthree(team *t,int made);
void rem_team_athree(team *t,int attempted);

#endif