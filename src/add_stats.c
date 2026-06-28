#include <stdio.h>
#include <stdlib.h>
#include "player.h"
#include "io.h"
#include "error.h"
#include "menu.h"
#include "validate_stats.h"
#include "stat_type.h"
#include "player_op.h"
#include "add_stats.h"

bool flag = false;

const char *messages[] = 
{
    "How many made 1 pointers you want to add: ",
    "How many attempted 1 pointers you want to add: ",
    "How many made 2 pointers you want to add: ",
    "How many attempted 2 pointers you want to add: ",
    "How many made 3 pointers you want to add: ",
    "How many attempted 3 pointers you want to add: ",
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
    get_off_rebounds,
    get_def_rebounds,
    get_rebounds,
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
    add_off_rebs,
    add_def_rebs,
    add_rebs,
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
void add_player_stats(team *t, int stat, int value)
{
    switch(stat)
    {
        case FT_MADE: add_team_mft(t, value); break;
        case FT_ATTEMPTED: add_team_aft(t, value); break;
        case TWO_MADE: add_team_mtwo(t, value); break;
        case TWO_ATTEMPTED: add_team_atwo(t, value); break;
        case THREE_MADE: add_team_mthree(t, value); break;
        case THREE_ATTEMPTED: add_team_athree(t, value); break;
        
        case OFF_REBOUNDS: 
            add_team_off(t, value);   
            add_team_rebs(t, value);  
            break;
            
        case DEF_REBOUNDS: 
            add_team_def(t, value);   
            add_team_rebs(t, value);  
            break;
            
        case ASSISTS: add_team_ass(t, value); break;
        case STEALS: add_team_steals(t, value); break;
        case BLOCKS: add_team_blocks(t, value); break;
        case TURNOVERS: add_team_tos(t, value); break;
        case FOULS: add_team_fouls(t, value); break;
    }
    if(stat == FT_MADE) add_team_points(t, value * 1);
    else if(stat == TWO_MADE) add_team_points(t, value * 2);
    else if(stat == THREE_MADE) add_team_points(t, value * 3);
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
void add(hashtable *ht,vector *vec,team *t,int stat)
{
    flag = false;
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
    if(stat >= REBOUNDS)     //In menu we dont need total rebs but we need it for team stats
    {
        stat++; 
    }
    //Validate matches
    if(stat!=MATCHES)
    {
        int val = value + get_vals[stat -1](player_found);
        if(!validate_match(player_found,val))    
        {
            error_message("Matches should be more than zero!!! Please update matches first!\n");
            free(name);
            return;
        }    
    }

    //Validate fouls
    if(stat == FOULS)
    {
        if(!validate_foul(player_found,value))
        {
            char msg[100];

            snprintf(msg, sizeof(msg),"Fouls cannot be more than %d!!!", get_matches(player_found) * 5);
            error_message(msg);
            free(name);
            return;
        }
    }

    //Check for made , attempted functions
    if(stat <= THREE_ATTEMPTED)
    {
        if(!validate_shots(player_found,stat,value)) 
        {
            error_message("Made cannot be more than total attempts!!! Please update attempted first!\n");
            free(name);
            return;
        }
    }

    //Handle rebounds
    if(stat>=OFF_REBOUNDS && stat<=DEF_REBOUNDS)
    {        
        flag = true;
    }


    add_vals[stat-1](player_found,value);
    if(stat<=THREE_ATTEMPTED) //If the stat is for made-attempted shots, calculate the percentage
    {
        if(stat%2==0) add_percent[stat/2-1](player_found);
        else add_percent[stat/2](player_found);
    }
    //After we are sure that the added stats are valid we insert them into the team stats
    if(stat <MATCHES) add_player_stats(t,stat,value); //We do not add matches here, we add only when user want to print those stats
    save_to_sql(vec);
    free(name);
}

//Function to add stats of a player
void add_stats(hashtable *ht,vector *vec,team *t)
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
        if(choice!=15 && is_valid) add(ht,vec,t,choice);
    }while(choice!=15);

}


bool add_pipe(hashtable *ht, vector *vec, team *t, int stat, char *name, int value){
    
    flag = false;
    //Search for this player in the hashtable
    player *player_found = search_hash(ht,name);

    if(!player_found)
    {
        error_message("ERROR: Player not found.\n");
        return false;
    } 

    if(stat >= REBOUNDS)     //In menu we dont need total rebs but we need it for team stats
    {
        stat++; 
    }
    if(stat!=MATCHES)
    {
        int val = value + get_vals[stat -1](player_found);
        if(!validate_match(player_found,val))    
        {
            error_message("ERROR: Matches should be more than zero!!! Please update matches first!\n");
            return false;
        }    
    }

    //Validate fouls
    if(stat == FOULS)
    {
        if(!validate_foul(player_found,value))
        {
           char msg[100];

            snprintf(msg, sizeof(msg),"ERROR: Fouls cannot be more than %d!!!", get_matches(player_found) * 5);
            error_message(msg);
            return false;
        }
    }

    //Check for made , attempted functions
    if(stat <= THREE_ATTEMPTED)
    {
        if(!validate_shots(player_found,stat,value)) 
        {
            error_message("ERROR: Made cannot be more than total attempts!!! Please update attempted first\n");
            return false;
        }
    }

    //Handle rebounds
    if(stat>=OFF_REBOUNDS && stat<=DEF_REBOUNDS)
    {        
        flag = true;
    }

    add_vals[stat-1](player_found,value);
    if(stat<=THREE_ATTEMPTED) //If the stat is for made-attempted shots, calculate the percentage
    {
        if(stat%2==0) add_percent[stat/2-1](player_found);
        else add_percent[stat/2](player_found);
    }
    //After we are sure that the added stats are valid we insert them into the team stats
    if(stat <MATCHES) add_player_stats(t,stat,value); //We do not add matches here, we add only when user want to print those stats
    save_to_sql(vec);
    return true;
}