#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "player.h"
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
    "How many rebounds you want to add: ",
    "How many assists you want to add: ",
    "How many steals you want to add: ",
    "How many blocks you want to add: ",
    "How many turnovers you want to add: ",
    "How many matches you want to add: "
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

//Function to remove a player from the list of the team
bool remove_player(hashtable **ht,vector **vec)
{
    clear_stdin();
    printf("Type the name of the player you want to remove: ");
    char *name = get_line();
    if(!name) return false;

    player *to_freed = delete_hash(*ht,name);
    if(!to_freed)
    {
        fprintf(stderr,"Player not found.\n");
        sleep(1);
        free(name);
        return true;
    }
    
    /*remove a player from the vector*/
    vector_remove_by_item(*vec,name,check_player);
    
    delete_player(to_freed); //delete the player only once
    free(name);
    return true;
    
}

//Function to add stats to one specific player
void add(hashtable *ht,int stat)
{
    clear_stdin();
    printf("Which player: ");
    char *name = get_line();
    if(!name) return;

    //Search for this player in the hashtable
    player *player_found = search_hash(ht,name);

    if(!player_found)
    {
        fprintf(stderr, "Player not found.\n");
        sleep(1);
        free(name);
        return;
    } 

    int value = 0;
    printf("%s",messages[stat-1]);
    if(scanf("%d",&value)!=1)
    {
        fprintf(stderr,"Wrong value\n");
        sleep(1);
        clear_stdin();
    }

    //Check for made , attempted functions
    if(stat-1 <= 5)
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
            fprintf(stderr,"Made cannot be more than total attempts!!!\n");
            sleep(2);
            free(name);
            return;
        }
    }


    add_vals[stat-1](player_found,value);
    if(stat-1<=5) 
    {
        if(stat%2==0) add_percent[stat/2-1](player_found);
        else add_percent[stat/2](player_found);
    }
    free(name);
}

//Function to add stats of a player
void add_stats(hashtable *ht)
{
    int choice = 0;
    do
    {
        system("clear");
        printf("Which stat you want to change: \n");
        printf("1.1p Made\n2.1p Attempted\n3.2p Made\n4.2p Attempted\n5.3p Made\n6.3p Attempted\n7.Rebounds\n8.Assists\n9.Steals\n10.Blocks\n11.Turnovers\n12.Matches\n13.Exit\n");
        printf("Type your choice: ");
        if(scanf("%d",&choice)!=1 || choice <1 || choice >13) 
        {
            fprintf(stderr,"Wrong value\n");
            sleep(1);
            clear_stdin();
            choice = 0;   
        }
        system("clear");
        add(ht,choice);
    }while(choice!=13);

}