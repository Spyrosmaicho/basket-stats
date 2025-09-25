#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"
#include "error.h"
#include "io.h"
#include "player_op.h"

#define FIELDS_SIZE 20

const char *fields[] = {
    "\"Name\"", "\"Points\"", "\"Rebounds\"","\"Off_Rebounds\"", "\"Def_Rebounds\"",
    "\"Assists\"", "\"Steals\"", "\"Blocks\"", "\"Turnovers\"", "\"Fouls\"", "\"Matches\"",
    "\"FT_Made\"", "\"FT_Attempted\"","\"Two_Made\"", "\"Two_Attempted\"", "\"Three_Made\"", "\"Three_Attempted\"",
    "\"FT_Percent\"","\"Two_Percent\"","\"Three_Percent\""
};


//Function to read a new player and add him to the list of the team
bool read_player(hashtable **ht,vector **vec)
{
    clear_stdin();
    printf("Type player's name: ");
    char *name = get_line();
    if(!name) return false;

    player *pl = create_player(name);

    //Insert the player into the hashtable
    player *same = NULL;
    if((same = insert_hash(*ht,name,pl))) 
    {
        vector_find_item(*vec,same,pl);
        delete_player(same);
    }
    else insert(*vec,pl); //insert the player into the vector
    system("clear");
    free(name);
    return true;
}

//Helper function to remove the stats of a player from the team stats
void remove_player_stats(team *t,player *pl)
{
    rem_team_points(t,get_points(pl));
    /*REBS*/rem_team_rebs(t,get_rebounds(pl)); rem_team_def(t,get_def_rebounds(pl)); rem_team_off(t,get_off_rebounds(pl));
    rem_team_ass(t,get_assists(pl));
    rem_team_steals(t,get_steals(pl));
    rem_team_blocks(t,get_blocks(pl));
    rem_team_tos(t,get_tos(pl));
    rem_team_fouls(t,get_fouls(pl));
    /*FTS*/rem_team_mft(t,get_ft_made(pl));rem_team_aft(t,get_ft_attempted(pl));
    /*2PT*/rem_team_mtwo(t,get_two_made(pl));rem_team_atwo(t,get_two_attempted(pl));
    /*3PT*/rem_team_mthree(t,get_three_made(pl));rem_team_athree(t,get_three_attempted(pl));
}

//Function to remove a player from the list of the team
bool remove_player(hashtable **ht,vector **vec,team *t)
{
    clear_stdin();
    printf("Type the name of the player you want to remove: ");
    char *name = get_line();
    if(!name) return false;

    player *to_freed = delete_hash(*ht,name);
    if(!to_freed)
    {
        error_message("Player not found.\n");
        free(name);
        return true;
    }
    
    /*remove a player from the vector*/
    vector_remove_by_item(*vec,name,check_player);
    
    //Remove the stats of the player from the team stats
    remove_player_stats(t,to_freed);

    delete_player(to_freed); //delete the player only once
    free(name);
    return true;
}

//Function to print an object of a player to a json file
void print_json_object(player *pl,FILE *file_json)
{
    fprintf(file_json," {\n\t\t");
    //First print the name
    int i = 0;
    fprintf(file_json,"%s: \"%s\",\n\t\t",fields[i++],get_name(pl));

    //Array for every stat(exclude name and three percentages)
    int array[FIELDS_SIZE-4] = {get_points(pl),get_rebounds(pl),get_off_rebounds(pl),get_def_rebounds(pl),get_assists(pl),
    get_steals(pl),get_blocks(pl),get_tos(pl),get_fouls(pl),get_matches(pl),
    get_ft_made(pl),get_ft_attempted(pl),get_two_made(pl),get_two_attempted(pl),get_three_made(pl),get_three_attempted(pl)};

    
    for(;i<FIELDS_SIZE-3;i++) fprintf(file_json,"%s: %d,\n\t\t",fields[i],array[i-1]);

    //Now print the three percentages
    array[11] > 0 ? fprintf(file_json,"%s: %.2lf,\n\t\t",fields[i++],get_1p_percentage(pl)) : fprintf(file_json,"%s: %.2lf,\n\t\t",fields[i++],0.0);
    array[13]> 0 ? fprintf(file_json,"%s: %.2lf,\n\t\t",fields[i++],get_2p_percentage(pl)) : fprintf(file_json,"%s: %.2lf,\n\t\t",fields[i++],0.0);
    array[15] > 0 ? fprintf(file_json,"%s: %.2lf\n\t",fields[i],get_3p_percentage(pl)) : fprintf(file_json,"%s: %.2lf\n\t",fields[i],0.0);
    fprintf(file_json," }");
}