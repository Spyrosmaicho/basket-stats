#include <stdio.h>
#include <stdlib.h>
#include "player.h"
#include "io.h"
#include "error.h"
#include "menu.h"
#include "validate_stats.h"
#include "stat_type.h"
#include "add_stats.h"


const char *messages[] = 
{
    "How many made 1 pointers you want to add: ",
    "How many attempted 1 pointers you want to add: ",
    "How many made 2 pointers you want to add: ",
    "How many attempted 2 pointers you want to add: ",
    "How many made 3 pointers you want to add: ",
    "How many attempted 3 pointers you want to add: ",
    "How many total rebounds you want to add: ",
    "How many offensive rebounds you want to add: ",
    "How many defensive rebounds you want to add: ",
    "How many assists you want to add: ",
    "How many steals you want to add: ",
    "How many blocks you want to add: ",
    "How many turnovers you want to add: ",
    "How many fouls you want to add: ",
    "How many matches you want to add: "
};

static int (*get_vals[])(player *) = 
{
    get_ft_made,
    get_ft_attempted,
    get_two_made,
    get_two_attempted,
    get_three_made,
    get_three_attempted,
    get_rebounds,
    get_off_rebounds,
    get_def_rebounds,
    get_assists,
    get_steals,
    get_blocks,
    get_tos,
    get_fouls
};

void (*add_vals[])(player *,int) = 
{
    add_1p_made,
    add_1p_attempted,
    add_2p_made,
    add_2p_attempted,
    add_3p_made,
    add_3p_attempted,
    add_rebs,
    add_off_rebs,
    add_def_rebs,
    add_ass,
    add_steals,
    add_blocks,
    add_tos,
    add_fouls,
    add_matches
};

void (*add_percent[])(player *) = 
{
    add_1p_percent,
    add_2p_percent,
    add_3p_percent
};

//Helper function to add the stats of a player into the team stats
void add_player_stats(team *t,player *pl,int stat)
{
    switch(stat)
    {
        case FT_MADE: add_team_mft(t,get_ft_made(pl)); break;
        case FT_ATTEMPTED: add_team_aft(t,get_ft_attempted(pl)); break;
        case TWO_MADE: add_team_mtwo(t,get_two_made(pl)); break;
        case TWO_ATTEMPTED: add_team_atwo(t,get_two_attempted(pl)); break;
        case THREE_MADE: add_team_mthree(t,get_three_made(pl)); break;
        case THREE_ATTEMPTED: add_team_athree(t,get_three_attempted(pl)); break;
        case REBOUNDS: add_team_rebs(t,get_rebounds(pl)); break;
        case OFF_REBOUNDS: add_team_off(t,get_off_rebounds(pl)); break;
        case DEF_REBOUNDS: add_team_def(t,get_def_rebounds(pl)); break;
        case ASSISTS: add_team_ass(t,get_assists(pl)); break;
        case STEALS: add_team_steals(t,get_steals(pl)); break;
        case BLOCKS: add_team_blocks(t,get_blocks(pl)); break;
        case TURNOVERS: add_team_tos(t,get_tos(pl)); break;
        case FOULS: add_team_fouls(t,get_fouls(pl)); break;
    }
    if(stat>= FT_MADE && stat <=THREE_ATTEMPTED) add_team_points(t,get_points(pl));
}
//Function to add simultaneously all the stats into a player
void add_all_player_stats(team *t,player *pl)
{
    add_team_mft(t,get_ft_made(pl)); 
    add_team_aft(t,get_ft_attempted(pl)); 
    add_team_mtwo(t,get_two_made(pl)); 
    add_team_atwo(t,get_two_attempted(pl)); 
    add_team_mthree(t,get_three_made(pl)); 
    add_team_athree(t,get_three_attempted(pl)); 
    add_team_rebs(t,get_rebounds(pl)); 
    add_team_off(t,get_off_rebounds(pl));
    add_team_def(t,get_def_rebounds(pl));
    add_team_ass(t,get_assists(pl)); 
    add_team_steals(t,get_steals(pl)); 
    add_team_blocks(t,get_blocks(pl)); 
    add_team_tos(t,get_tos(pl)); 
    add_team_fouls(t,get_fouls(pl)); 
    add_team_points(t,get_points(pl));
}
//Function to add stats to one specific player
void add(hashtable *ht,team *t,int stat)
{
    clear_stdin();
    printf("Which player: ");
    char *name = get_line();
    if(!name) return;

    //Search for this player in the hashtable
    player *player_found = search_hash(ht,name);

    if(!player_found)
    {
        error_message("Player not found.\n");
        free(name);
        return;
    } 

    int value = 0;
    printf("%s",messages[stat-1]);
    if(scanf("%d",&value)!=1 || value<=0)
    {
        error_message("Wrong value.\n");
        free(name);
        clear_stdin();
        return;
    }

    //Validate matches
    if(stat!=MATCHES)
    {
        int val = value + get_vals[stat -1](player_found);
        if(!validate_match(player_found,val))    
        {
            error_message("Matches should be more than zero!!!\n");
            free(name);
            return;
        }    
    }

    //Validate fouls
    if(stat == FOULS)
    {
        if(!validate_foul(player_found,value))
        {
            error_message("Fouls cannot be more than 5!!!\n");
            free(name);
            return;
        }
    }

    //Check for made , attempted functions
    if(stat <= THREE_ATTEMPTED)
    {
        if(!validate_shots(player_found,stat,value)) 
        {
            error_message("Made cannot be more than total attempts!!!\n");
            free(name);
            return;
        }
    }

    //Handle rebounds
    if(stat>=OFF_REBOUNDS && stat<=DEF_REBOUNDS)
    {        
        int total =0 ,def = 0,off=0;

        if(!validate_rebs(player_found,stat,value,&total,&off,&def)) 
        {
            error_message("Offensive/Defensive Rebounds cannot be more than total Rebounds!!!\n");
            free(name);
            return;
        }

        //If user added off rebs we can found def rebs, because we also know the total rebs 
        if(stat==OFF_REBOUNDS) add_vals[stat](player_found,total - off);
        else add_vals[stat-2](player_found,total-def);
    }


    add_vals[stat-1](player_found,value);
    if(stat<=THREE_ATTEMPTED) //If the stat is for made-attempted shots, calculate the percentage
    {
        if(stat%2==0) add_percent[stat/2-1](player_found);
        else add_percent[stat/2](player_found);
    }
    //After we are sure that the added stats are valid we insert them into the team stats
    if(stat <MATCHES) add_player_stats(t,player_found,stat); //We do not add matches here, we add only when user want to print those stats
    free(name);
}

//Function to add stats of a player
void add_stats(hashtable *ht,team *t)
{
    int choice = 0;
    do
    {
         bool is_valid = true;
        system("clear");
        add_stats_menu();
       
        printf("Type your choice: ");
        if(scanf("%d",&choice)!=1 || choice <1 || choice >16) 
        {
            error_message("Wrong value.\n");
            clear_stdin();
            is_valid = false;
            choice = 0;   
        }
        system("clear");
        if(choice!=16 && is_valid) add(ht,t,choice);
    }while(choice!=16);

}