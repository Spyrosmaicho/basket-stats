#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"
#include "io.h"
#include "player_op.h"



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
    "How many matches you want to add: "
};

typedef enum {
    FT_MADE = 1,
    FT_ATTEMPTED,
    TWO_MADE,
    TWO_ATTEMPTED,
    THREE_MADE,
    THREE_ATTEMPTED,
    REBOUNDS,
    OFF_REBOUNDS,
    DEF_REBOUNDS,
    ASSISTS,
    STEALS,
    BLOCKS,
    TURNOVERS,
    MATCHES
} StatType;

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
    add_matches
};

void (*add_percent[])(player *) = 
{
    add_1p_percent,
    add_2p_percent,
    add_3p_percent
};


int made_shots(player *pl,int stat)
{
    switch(stat)
    {
        case 1: return get_ft_made(pl);
        case 3: return get_two_made(pl);
        case 5: return get_three_made(pl);
    }
    return 0;
}

int attempted_shots(player *p, int stat) 
{
    switch (stat) 
    {
        case 2: return get_ft_attempted(p);
        case 4: return get_two_attempted(p);
        case 6: return get_three_attempted(p);
    }
    return 0;
}

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

//Helper function to add the stats of a player into the team stats
void add_player_stats(team *t,player *pl)
{
    add_team_points(t,get_points(pl));
    add_team_rebs(t,get_rebounds(pl));
    add_team_def(t,get_def_rebounds(pl));
    add_team_off(t,get_off_rebounds(pl));
    add_team_ass(t,get_assists(pl));
    add_team_steals(t,get_steals(pl));
    add_team_blocks(t,get_blocks(pl));
    add_team_tos(t,get_tos(pl));
    add_team_mft(t,get_ft_made(pl));
    add_team_aft(t,get_ft_attempted(pl));
    add_team_mtwo(t,get_two_made(pl));
    add_team_atwo(t,get_two_attempted(pl));
    add_team_mthree(t,get_three_made(pl));
    add_team_athree(t,get_three_attempted(pl));
}
//Helper function to remove the stats of a player from the team stats
void remove_player_stats(team *t,player *pl)
{
    rem_team_points(t,get_points(pl));
    rem_team_rebs(t,get_rebounds(pl));
    rem_team_def(t,get_def_rebounds(pl));
    rem_team_off(t,get_off_rebounds(pl));
    rem_team_ass(t,get_assists(pl));
    rem_team_steals(t,get_steals(pl));
    rem_team_blocks(t,get_blocks(pl));
    rem_team_tos(t,get_tos(pl));
    rem_team_mft(t,get_ft_made(pl));
    rem_team_aft(t,get_ft_attempted(pl));
    rem_team_mtwo(t,get_two_made(pl));
    rem_team_atwo(t,get_two_attempted(pl));
    rem_team_mthree(t,get_three_made(pl));
    rem_team_athree(t,get_three_attempted(pl));
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

    remove_player_stats(t,player_found);

    int value = 0;
    printf("%s",messages[stat-1]);
    if(scanf("%d",&value)!=1)
    {
        error_message("Wrong value.\n");
        clear_stdin();
    }

    //Check for made , attempted functions
    if(stat <= THREE_ATTEMPTED)
    {
        int made =  0,attempts = 0;
        if(stat % 2 == 1) //Made shots
        {
            made = made_shots(player_found,stat) + value;
            attempts = attempted_shots(player_found,stat+1);
        }
        else //Attempted shots
        {
            attempts = attempted_shots(player_found,stat) + value;
            made = made_shots(player_found,stat-1);
        }

        if(made > attempts) 
        {
            error_message("Made cannot be more than total attempts!!!\n");
            free(name);
            return;
        }
    }

    //Handle rebounds
    if(stat>=OFF_REBOUNDS && stat<=DEF_REBOUNDS)
    {        
        int total = get_rebounds(player_found);
        int off=0,def=0;
        //Offensive rebs
        if(stat==OFF_REBOUNDS) off = get_off_rebounds(player_found) + value;
        else def = get_def_rebounds(player_found) + value;

        if(off > total || def > total) 
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
    add_player_stats(t,player_found);
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
        if(scanf("%d",&choice)!=1 || choice <1 || choice >15) 
        {
            error_message("Wrong value.\n");
            clear_stdin();
            is_valid = false;
            choice = 0;   
        }
        system("clear");
        if(choice!=15 && is_valid) add(ht,t,choice);
    }while(choice!=15);

}