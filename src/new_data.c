#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "io.h"
#include "player_op.h"
#include "menu.h"
#include "new_data.h"

//New data menu
void new_data(hashtable *ht,vector *vec)
{
    size_t choice = 0;
    do
    {
        show_new_data_menu();
        printf("Type your choice: ");
        if(scanf("%lu",&choice)!=1 || choice<1 || choice >7) 
        {
            error_message("Error occured.\n");
            clear_stdin();
            choice = 0; //make it zero because we dont want switch to choose a case (previous value was saved!)
        }
        system("clear");
        

        switch(choice)
        {
            case 1:
                ;    
                bool check = read_player(&ht,&vec);
                if(!check) error_handler(ht,vec);
                break;
            case 2:
                ;
                if(!vec || !ht)
                {
                    error_message("Error occured.\n");
                    break;
                }
                bool check2 = remove_player(&ht,&vec);
                if(!check2) error_handler(ht,vec);
                break;
                case 3: 
                    add_stats(ht);
                    break;
                case 4:
                    //If the vector is empty there are no players 
                    if(!vec || empty(vec))
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
                        if(scanf("%d",&stat)!=1 || stat<1 || stat>13)
                        {
                            error_message("Wrong choice.\n");
                            clear_stdin();
                            system("clear");
                            go_back = true; //We dont want to go back to the previous menu if there's a mistake from user
                        }
                        system("clear");
                        if(stat!=13 && !go_back)  
                        {
                            print_top_players(vec,stat);
                            system("clear");
                        }
                    }while(stat!=13 && go_back);
                    break;
                case 5:
                    ;
                    if(!ht) 
                    {
                       error_message("Team is empty. No players to display.\n");
                        break;
                    }
                    print_one_player(ht);
                    break;
                case 6:
                    if (!vec || empty(vec)) 
                    {
                       error_message("Team is empty. No players to display.\n");
                        break;
                    }
                    clear_stdin();
                    printf("Type the name of the file: ");
                    char *filename = get_line();
                    if(!filename) error_handler(ht,vec);
                    putchar('\n'); //for good visualization
                    print_all_players(vec,filename);
                    free(filename);
                    break;
            }

            system("clear");
    }while(choice!=7);
}