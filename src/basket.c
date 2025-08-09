#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "basket.h"

//Function to use getline
char *get_func(void)
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
bool read_player(avl **avl)
{
    clear_stdin();
    printf("Type player's name: ");
    char *buff = get_func();
    if(!buff) return false;
    int size = get_sizeof_player();
    *avl = insert_avl(avl,buff,player_cmp,size);

    system("clear");
    free(buff);
    return true;
}

//Function to remove a player from the list of the team
bool rem(avl **node)
{
    clear_stdin();
    printf("Type the name of the player you want to remove: ");
    char *buff = get_func();
    if(!buff) return false;

    avl *old_root = *node;
    *node = delete_avl(node, buff, player_cmp, free_val);

    //A problem occured and the player could not be freed.
    if(!(*node)) 
    {
        fprintf(stderr,"Player not found.\n");
        sleep(1);
        free(buff);
        return true;
    }

    if (*node == old_root) 
    {
        fprintf(stderr, "Player not found.\n");
        sleep(1);
        free(buff);
        return true;
    }

    free(buff);
    return true;
    
}

//Function to add stats to one specific player
void add(avl *root,int stat)
{
    clear_stdin();
    printf("Which player: ");
    char *buff = get_func();
    if(!buff) return;

    avl *found = search_avl(root,buff,player_cmp);

    if(!found)
    {
        fprintf(stderr, "Player not found.\n");
        sleep(1);
        free(buff);
        return;
    }

    player *new = avl_val(found);

    switch(stat)
    {
        case 1:
            ;
            int new_points = 0;
            printf("How many points you want to add: ");
            if(scanf("%d",&new_points)!=1) 
            {
                fprintf(stderr,"Wrong value\n");
                sleep(1);
                clear_stdin();
            }
            add_points(new_points,new);
            break;
        case 2:
            ;
            int new_rebs = 0;
            printf("How many rebounds you want to add: ");
            if(scanf("%d",&new_rebs)!=1) 
            {
                fprintf(stderr,"Wrong value\n");
                sleep(1);
                clear_stdin();
            }
            add_rebs(new_rebs,new);
            break;
        case 3:
            ;
            int new_ass = 0;
            printf("How many assists you want to add: ");
            if(scanf("%d",&new_ass)!=1) 
            {
                fprintf(stderr,"Wrong value\n");
                sleep(1);
                clear_stdin();
            }
            add_ass(new_ass,new);
            break;
        case 4:
            ;
            int new_steals = 0;
            printf("How many steals you want to add: ");
            if(scanf("%d",&new_steals)!=1) 
            {
                fprintf(stderr,"Wrong value\n");
                sleep(1);
                clear_stdin();
            }
            add_steals(new_steals,new);
            break;
        case 5:
            ;
            int new_blocks = 0;
            printf("How many blocks you want to add: ");
            if(scanf("%d",&new_blocks)!=1) 
            {
                fprintf(stderr,"Wrong value\n");
                sleep(1);
                clear_stdin();
            }
            add_blocks(new_blocks,new);
            break;
        case 6:
            ;
            int new_tos = 0;
            printf("How many turnovers you want to add: ");
            if(scanf("%d",&new_tos)!=1) 
            {
                fprintf(stderr,"Wrong value\n");
                sleep(1);
                clear_stdin();
            }
            add_tos(new_tos,new);
            break;
        case 7:
            ;
            int new_match = 0;
            printf("How many matches you want to add: ");
            if(scanf("%d",&new_match)!=1) 
            {
                fprintf(stderr,"Wrong value\n");
                sleep(1);
                clear_stdin();
            }
            add_matches(new_match,new);
            break;
    }
    free(buff);
}



//Function to add stats of a player
void add_stats(avl *avl)
{
    int choice = 0;
    do
    {
        system("clear");
        printf("Which stat you want to change: \n");
        printf("1.Points\n2.Rebounds\n3.Assists\n4.Steals\n5.Blocks\n6.Turnovers\n7.Matches\n8.Exit\n");
        printf("Type your choice: ");
        if(scanf("%d",&choice)!=1) 
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
                add(avl,1);
                break;
            case 2:
                add(avl,2);
                break;
            case 3:
                add(avl,3);
                break;
            case 4:
                add(avl,4);
                break;
            case 5:
                add(avl,5);
                break;
            case 6:
                add(avl,6);
                break;
            case 7:
                add(avl,7);
                break;
        }
    }while(choice!=8);
}

//Function to print stats of a specific player
void print_stats(avl *root)
{
    clear_stdin();
    printf("Which player: ");
    char *buff = get_func();
    if(!buff) return;

    avl *found  = search_avl(root,buff,player_cmp);

    if(!found)
    {
        fprintf(stderr, "Player not found.\n");
        sleep(1);
        free(buff);
        return;
    }

    player *new = avl_val(found); 
    char *name = get_name(new);
    int points = get_points(new);
    int rebs = get_rebounds(new);
    int ass = get_assists(new);
    int steals = get_steals(new);
    int blocks = get_blocks(new);
    int tos = get_tos(new);
    int matches = get_matches(new);
    system("clear");
    printf("Player: %s\n",name);
    line();
    printf("Points: %d\n",points);
    printf("Rebounds: %d\n",rebs);
    printf("Assists: %d\n",ass);
    printf("Steals: %d\n",steals);
    printf("Blocks: %d\n",blocks);
    printf("Turnovers: %d\n",tos);
    printf("Matches: %d\n",matches);
    sleep(4);
    free(buff);
}

//Function to print stats of all players
void print_team(avl *avl,char *filename)
{
    FILE *file = fopen(filename, "w");
    if (!file ) 
    {
        fprintf(stderr,"Cannot open file\n");
        return;
    }
    printf("%-10s | %7s | %8s | %7s | %6s | %6s | %5s | %7s\n", 
       "Player", "Points", "Rebounds", "Assists", "Steals", "Blocks", "Tos", "Matches");
    
        fprintf(file,"%-10s | %7s | %8s | %7s | %6s | %6s | %5s | %7s\n", 
       "Player", "Points", "Rebounds", "Assists", "Steals", "Blocks", "Tos", "Matches");

    
    inorder(avl,file);

    sleep(4);
    fclose(file);
}

//Function to insert all stats of a player that are found in a file. 
bool insert_all_stats(avl *root,char *name,int points,int rebs,int ass,int steals,int blocks,int tos,int matches)
{
    avl *node = search_avl(root,name,player_cmp);
    if(!node) return false; //maybe this never happens

    player *p = avl_val(node);
    add_points(points,p);
    add_rebs(rebs,p);
    add_ass(ass,p);
    add_steals(steals,p);
    add_blocks(blocks,p);
    add_tos(tos,p);
    add_matches(matches,p);

    return true;
}
//Function to get the file with the players 
avl *load_file(avl *avl)
{
    printf("Type the name of the file: ");

    char *filename = get_func();
    if(!filename) return NULL;

    FILE *f = fopen(filename,"r");
    if(!f) return NULL;

    //free filename (caller should free the returned string of get_func)
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
        return NULL;
    }

    if(buff[numCh-1] == '\n')
        buff[numCh-1] = '\0';

    free(buff);

    //READ THE DATA FROM THE FILE USING FSCANF. THEN INSERT THEM INTO THE avl
    char name[100];
    int points = 0 ,rebs = 0,ass = 0,steals=0,blocks=0,tos=0,matches=0;
    int size = get_sizeof_player();
    int res = 0;
    while((res = fscanf(f," %99[^|] | %d | %d | %d | %d | %d | %d | %d",name,&points,&rebs,&ass,&steals,&blocks,&tos,& matches)) == 8)
    {
        //Change the spaces in the end of the string with null
        int len = strlen(name);
        while (len > 0 && name[len - 1] == ' ') name[--len] = '\0';



        
        avl = insert_avl(&avl,name,player_cmp,size);
        bool check = insert_all_stats(avl,name,points,rebs,ass,steals,blocks,tos,matches);
        if(!check) 
        {
            fclose(f);
            return NULL;
        }

    }
    if(res < 8 && res!=EOF) 
    {
        fprintf(stderr,"A stat is wrong.\n");
        sleep(1.5);
    }
    fclose(f);
    return avl;
}