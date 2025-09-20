#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "basket.h"
#include "player.h"

//Function to use getline
char *get_line(void)
{
    char *buff = NULL;
    size_t sizeAllocated = 0;
    ssize_t numCh = 0;
    if((numCh = getline(&buff, &sizeAllocated, stdin)) ==-1 )
    {
        free(buff);
        fprintf(stderr,"Error occured.\n");
        return NULL;
    }

    if(buff[numCh-1] == '\n')
        buff[numCh-1] = '\0';

    return buff;
}

//Helper function to clear stdin in order to make getline work properly
void clear_stdin(void) 
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

//For printing purposes
void line(void)
{
    printf("----------------\n");
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

    switch(stat)
    {
        case 1:
            ;
            int ft_made = 0;
            printf("How many made 1 pointers you want to add: ");
            if(scanf("%d",&ft_made)!=1)
            {
                 fprintf(stderr,"Wrong value\n");
                sleep(1);
                clear_stdin();
            }
            int ft_attempts = get_ft_attempted(player_found);
            if(ft_made <= ft_attempts)
            {
                add_1p_made(player_found,ft_made);
                add_1p_percent(player_found);
            }
            else{
                fprintf(stderr,"Made cannot be more than total attempts!!!\n");
                sleep(2);
            }
            break;
        case 2:
             ;
            int ft_attempted = 0;
            printf("How many made 1 pointers you want to add: ");
            if(scanf("%d",&ft_attempted)!=1)
            {
                 fprintf(stderr,"Wrong value\n");
                sleep(1);
                clear_stdin();
            }
            int mades = get_ft_made(player_found);
            if(mades <= ft_attempted)
            {
                add_1p_attempted(player_found,ft_attempted);
                add_1p_percent(player_found);
            }
            else
            {
                fprintf(stderr,"Made shots cannot be more than total attempts!!!\n");
                sleep(2);
            }
            break;
        case 3:
            ;
            int tp_made = 0;
            printf("How many made 2 pointers you want to add: ");
            if(scanf("%d",&tp_made)!=1)
            {
                fprintf(stderr,"Wrong value\n");
                sleep(1);
                clear_stdin();
            }
            int two_attempts = get_two_attempted(player_found);
            if(tp_made <= two_attempts)
            {
                add_2p_made(player_found,tp_made);
                add_2p_percent(player_found);
            }
            else
            {
                fprintf(stderr,"Made shots cannot be more than total attempts!!!\n");
                sleep(2);
            }
            break;
        case 4:
            ;
            int tp_attempted = 0;
            printf("How many attempted 2 pointers you want to add: ");
            if(scanf("%d",&tp_attempted)!=1)
            {
                fprintf(stderr,"Wrong value\n");
                sleep(1);
                clear_stdin();
            }
            int twos_made = get_two_made(player_found);
            if(twos_made <= tp_attempted)
            {
                add_2p_attempted(player_found,tp_attempted);
                add_2p_percent(player_found);
            }
            else
            {
                 fprintf(stderr,"Made shots cannot be more than total attempts!!!\n");
                sleep(2);
            }
            break;
        case 5:
            ;
            int tp3_made = 0;
            printf("How many made 3 pointers you want to add: ");
            if(scanf("%d",&tp3_made)!=1)
            {
                fprintf(stderr,"Wrong value\n");
                sleep(1);
                clear_stdin();
            }
            int three_attempts = get_three_attempted(player_found);
            if(tp3_made <= three_attempts)
            {
                add_3p_made(player_found,tp3_made);
                add_3p_percent(player_found);
            }
            else
            {
                 fprintf(stderr,"Made shots cannot be more than total attempts!!!\n");
                sleep(2);
            }
            break;
        case 6:
             ;
            int tp3_attempted = 0;
            printf("How many attempted 3 pointers you want to add: ");
            if(scanf("%d",&tp3_attempted)!=1)
            {
                fprintf(stderr,"Wrong value\n");
                sleep(1);
                clear_stdin();
            }
            int three_made = get_three_made(player_found);
            if(three_made <= tp3_attempted)
            {
                add_3p_attempted(player_found,tp3_attempted);
                add_3p_percent(player_found);
            }
            else
            {
                 fprintf(stderr,"Made shots cannot be more than total attempts!!!\n");
                sleep(2);
            }    
            break;   
        case 7:
            ;
            int new_rebs = 0;
            printf("How many rebounds you want to add: ");
            if(scanf("%d",&new_rebs)!=1) 
            {
                fprintf(stderr,"Wrong value\n");
                sleep(1);
                clear_stdin();
            }
            add_rebs(player_found,new_rebs);
            break;
        case 8:
            ;
            int new_ass = 0;
            printf("How many assists you want to add: ");
            if(scanf("%d",&new_ass)!=1) 
            {
                fprintf(stderr,"Wrong value\n");
                sleep(1);
                clear_stdin();
            }
            add_ass(player_found,new_ass);
            break;
        case 9:
            ;
            int new_steals = 0;
            printf("How many steals you want to add: ");
            if(scanf("%d",&new_steals)!=1) 
            {
                fprintf(stderr,"Wrong value\n");
                sleep(1);
                clear_stdin();
            }
            add_steals(player_found,new_steals);
            break;
        case 10:
            ;
            int new_blocks = 0;
            printf("How many blocks you want to add: ");
            if(scanf("%d",&new_blocks)!=1) 
            {
                fprintf(stderr,"Wrong value\n");
                sleep(1);
                clear_stdin();
            }
            add_blocks(player_found,new_blocks);
            break;
        case 11:
            ;
            int new_tos = 0;
            printf("How many turnovers you want to add: ");
            if(scanf("%d",&new_tos)!=1) 
            {
                fprintf(stderr,"Wrong value\n");
                sleep(1);
                clear_stdin();
            }
            add_tos(player_found,new_tos);
            break;
        case 12:
            ;
            int new_match = 0;
            printf("How many matches you want to add: ");
            if(scanf("%d",&new_match)!=1) 
            {
                fprintf(stderr,"Wrong value\n");
                sleep(1);
                clear_stdin();
            }
            add_matches(player_found,new_match);
            break;
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
        switch(choice)
        {
            case 1:
                add(ht,1);
                break;
            case 2:
                add(ht,2);
                break;
            case 3:
                add(ht,3);
                break;
            case 4:
                add(ht,4);
                break;
            case 5:
                add(ht,5);
                break;
            case 6:
                add(ht,6);
                break;
            case 7:
                add(ht,7);
                break;
            case 8:
                add(ht,8);
                break;
            case 9:
                add(ht,9);
                break;
            case 10:
                add(ht,10);
                break;
            case 11:
                add(ht,11);
                break;
            case 12:
                add(ht,12);
                break;
        }
    }while(choice!=13);

}

//Function to print stats of a specific player
void print_one_player(hashtable *ht)
{
    clear_stdin();
    printf("Which player: ");
    char *name = get_line();
    if(!name) return;

    player *player_found = search_hash(ht,name);

    if(!player_found)
    {
        fprintf(stderr, "Player not found.\n");
        sleep(1);
        free(name);
        return;
    }
 
    char *name_pl = get_name(player_found);
    int points = get_points(player_found);
    int rebs = get_rebounds(player_found);
    int ass = get_assists(player_found);
    int steals = get_steals(player_found);
    int blocks = get_blocks(player_found);
    int tos = get_tos(player_found);
    int matches = get_matches(player_found);
    int ft_made = get_ft_made(player_found);
    int ft_attempted = get_ft_attempted(player_found);
    int two_made = get_two_made(player_found);
    int two_attempted = get_two_attempted(player_found);
    int three_made = get_three_made(player_found);
    int three_attempted = get_three_attempted(player_found);
    double one_percent = 0.0;
    if(ft_attempted!=0) one_percent = get_1p_percentage(player_found);
    double two_percent = 0.0;
    if(two_attempted!=0)two_percent = get_2p_percentage(player_found);
    double three_percent = 0.0;
    if(three_attempted!=0) three_percent = get_3p_percentage(player_found);
    system("clear");
    printf("Player: %s\n",name_pl);
    line();
    printf("Points: %d\n",points);
    printf("Rebounds: %d\n",rebs);
    printf("Assists: %d\n",ass);
    printf("Steals: %d\n",steals);
    printf("Blocks: %d\n",blocks);
    printf("Turnovers: %d\n",tos);
    printf("Matches: %d\n",matches);
    printf("Free Throws - Percentage: %d / %d - %.2lf%%\n",ft_made,ft_attempted,one_percent);
    printf("Two Pointers - Percentage: %d / %d - %.2lf%%\n",two_made,two_attempted,two_percent);
    printf("Three Pointers - Percentage: %d / %d - %.2lf%%\n",three_made,three_attempted,three_percent);
    sleep(4);
    free(name);
}

//Function to print stats of all players
void print_all_players(vector *vec,char *filename)
{
    FILE *file = fopen(filename, "w");
    if (!file ) 
    {
        fprintf(stderr,"Cannot open file\n");
        return;
    }

    int len = vector_biggest_data(vec,player_name_len);

    printf("%-*s | %7s | %8s | %7s | %6s | %6s | %5s | %7s | %7s     | %7s     | %7s     | %6s | %6s | %6s\n",len,
    "Name", "Points", "Rebounds", "Assists", "Steals", "Blocks", "Tos", "Matches", "1pt"
    ,"2pt", "3pt","1pt %" ,"2pt %", "3pt %");
    
        fprintf(file,"%-*s | %7s | %8s | %7s | %6s | %6s | %5s | %7s | %7s     | %7s     | %7s     | %6s | %6s | %6s\n",len,
    "Name", "Points", "Rebounds", "Assists", "Steals", "Blocks", "Tos", "Matches", "1pt"
    ,"2pt", "3pt","1pt %" ,"2pt %", "3pt %");

    int numsSize = vec_index(vec);
    for(int i = 0;i<numsSize;i++)
    {
        player *pl = vec_data(vec,i);
        print_player(pl,file,len);
    }
    

    sleep(4);
    fclose(file);
}

//Function to get the file with the players 
bool load_file(hashtable **ht,vector **vec)
{
    printf("Type the name of the file: ");

    char *filename = get_line();
    if(!filename) return false;

    FILE *f = fopen(filename,"r");
    if(!f) return false;

    //free filename (caller should free the returned string of get_line)
    free(filename);

    //Read the first line of the file
    char *buff = NULL;
    size_t sizeAllocated = 0;
    ssize_t numCh = 0;
    if((numCh = getline(&buff, &sizeAllocated, f)) ==-1 )
    {
        free(buff);
        fclose(f);
        fprintf(stderr,"Error occured.\n");
        return 0;
    }

    if(buff[numCh-1] == '\n')
        buff[numCh-1] = '\0';

    free(buff);

    //READ THE DATA FROM THE FILE USING FSCANF. THEN INSERT THEM INTO THE hashtable and the vector
    char name[100];
    int rebs = 0,ass = 0,steals=0,blocks=0,tos=0,matches=0,ft_made = 0,ft_attempted = 0,two_made = 0,two_attempted = 0,three_made = 0,three_attempted = 0;
    int res = 0;
    while((res = fscanf(f," %99[^|] | %d / %d | %d / %d | %d / %d | %d | %d | %d | %d | %d | %d",
        name,&ft_made,&ft_attempted,&two_made,&two_attempted,&three_made,&three_attempted,&rebs,&ass,&steals,&blocks,&tos,& matches)) == 13)
    {
        //This cannot happen. It's not true
        if(two_made > two_attempted || three_made > three_attempted || ft_made>ft_attempted) 
        {
            fclose(f);
            return false;
        }
        //Change the spaces in the end of the string with null
        int len = strlen(name);
        while (len > 0 && name[len - 1] == ' ') name[--len] = '\0';
        player *pl = create_player(name);

        int array_of_stats[12] = {ft_made,two_made,three_made,ft_attempted,two_attempted,three_attempted,rebs,ass,steals,blocks,tos,matches};
        insert_player_stats(pl,array_of_stats);

        //Insert the player into the hashtable
        player *same = NULL;
        if((same = insert_hash(*ht,name,pl)))
        {
            vector_find_item(*vec,same,pl);
            delete_player(same); 
        }
        else insert(*vec,pl); //insert the player into the vector

    }
    if(res < 12 && res!=EOF) 
    {
        fprintf(stderr,"A stat is wrong.\n");
        sleep(1.5);
        fclose(f);
        return false;
    }
    fclose(f);
    return true;
}

//Function to print the top 3 players according to user's choice
void print_top_players(vector *vec,int stat)
{
    int len = vector_biggest_data(vec,player_name_len);
   //Sort the vector 
   switch(stat)
    {
        case 1: 
            vector_sort(vec,cmp_points);
            break;
        case 2: 
            vector_sort(vec,cmp_rebs);
            break;
        case 3: 
            vector_sort(vec,cmp_ass);
            break;
        case 4: 
            vector_sort(vec,cmp_steals);
            break;
        case 5: 
            vector_sort(vec,cmp_blocks);
            break;
        case 6: 
            vector_sort(vec,cmp_tos);
            break;
        case 7: 
            vector_sort(vec,cmp_matches);
            break;
        case 8:
            vector_sort(vec,cmp_ft_percent);
            break;
        case 9:
            vector_sort(vec,cmp_two_percent);
            break;
        case 10:
            vector_sort(vec,cmp_three_percent);
            break;
    }
    //print header
    printf("%-*s | %7s | %8s | %7s | %6s | %6s | %5s | %7s | %7s     | %7s     | %7s     | %6s | %6s | %6s\n",len,
    "Name", "Points", "Rebounds", "Assists", "Steals", "Blocks", "Tos", "Matches", "1pt"
    ,"2pt", "3pt","1pt %" ,"2pt %", "3pt %");

    int num = vec_index(vec);
    //print first 3 players
    if(num>=3) 
    {
        for(int i = 0;i<3;i++) print_player(vec_data(vec,i),NULL,len);
        sleep(4);
    }
    else
    {
        for(int i = 0;i<num;i++) print_player(vec_data(vec,i),NULL,len);
        sleep(4);
    }
}


