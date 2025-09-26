#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "io.h"
#include "error.h"
#include "add_stats.h"
#include "player_op.h"
#include "menu.h"
#include "new_data.h"

//New data menu
void new_data(hashtable **ht,vector **vec,team **t)
{
    if(!(*ht) && !(*vec) && !(*t)) 
    {
        *ht = create_hashtable(15);
        *vec = init(15);
        *t = create_team();
    }
    size_t choice = 0;
    do
    {
        show_new_data_menu();
        printf("Type your choice: ");
        if(scanf("%lu",&choice)!=1 || choice<1 || choice >8) 
        {
            error_message("Wrong choice.\n");
            clear_stdin();
            choice = 0; //make it zero because we dont want switch to choose a case (previous value was saved!)
        }
        system("clear");
        

        switch(choice)
        {
            case 1:
                ;
                if(!read_player(ht,vec)) error_handler(*ht,*vec,*t,"Could not read player.\n");
                break;
            case 2:
                ;
                if(!(*vec) || !(*ht))
                {
                    error_message("There are no players to remove.\n");
                    break;
                }
                if(!remove_player(ht,vec,*t)) error_handler(*ht,*vec,*t,"Could not remove player.\n");
                break;
                case 3: 
                    add_stats(*ht,*t);
                    break;
                case 4:
                    //If the vector is empty there are no players 
                    if(!(*vec) || empty(*vec))
                    {
                        error_message("Team is empty. No players to display.\n");
                        break;
                    }
                    ;
                    int stat = 0;
                    bool go_back = false;
                    do
                    {
                        go_back = false;
                        show_top_menu();
                        printf("Type your choice: ");
                        if(scanf("%d",&stat)!=1 || stat<1 || stat>14)
                        {
                            error_message("Wrong choice.\n");
                            clear_stdin();
                            system("clear");
                            go_back = true; //We dont want to go back to the previous menu if there's a mistake from user
                        }
                        system("clear");
                        if(stat!=14 && !go_back)  
                        {
                            print_top_players(*vec,stat);
                            system("clear");
                        }
                    }while(stat!=14 && go_back);
                    break;
                case 5:
                    ;
                    if(!(*ht)) 
                    {
                       error_message("Team is empty. No players to display.\n");
                        break;
                    }
                    print_one_player(*ht);
                    break;
                case 6:
                    if (!(*vec) || empty(*vec)) 
                    {
                       error_message("Team is empty. No players to display.\n");
                        break;
                    }
                    clear_stdin();
                    printf("Type the name of the txt file: ");
                    char *filename1 = get_line();
                    if(!filename1) error_handler(*ht,*vec,*t,"Could not read txt file.\n");
                    system("clear");
                    printf("Type the name of the json file: ");
                    char *filename2 = get_line();
                    if(!filename2)
                    {
                        free(filename1);
                        error_handler(*ht,*vec,*t,"Could not read json file.\n");
                    }
                    putchar('\n');
                    system("clear");
                    print_all_players(*vec,filename1,filename2);
                    free(filename1);
                    free(filename2);
                    break;
                case 7:
                    if (!(*vec) || empty(*vec)) 
                    {
                       error_message("Team is empty. No players to display.\n");
                        break;
                    }
                    clear_stdin();
                    printf("Type the name of the txt file: ");
                    char *filename3 = get_line();
                    if(!filename3) error_handler(*ht,*vec,*t,"Could not read txt file.\n");
                    system("clear");
                    printf("Type the name of the json file: ");
                    char *filename4 = get_line();
                    if(!filename4)
                    {
                        free(filename3);
                        error_handler(*ht,*vec,*t,"Could not read json file.\n");
                    }
                    putchar('\n'); //for good visualization
                    system("clear");
                    print_team_stats(*vec,*t,filename3,filename4);
                    free(filename3);
                    free(filename4);
                    break;
            }
            system("clear");
    }while(choice!=8);
}