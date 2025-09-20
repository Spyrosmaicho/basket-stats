#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "vector.h"
#include "hashtable.h"
#include "player.h"
#include "basket.h"

int main(void)
{
    //Create the hashtable and the vector for 15 players
    bool is_freed = false;
    hashtable *ht = create_hashtable(15);
    vector *vec = init(15);
    int user = 0;
    do
    {
        printf("1. New data\n2. Old data\n3. Exit\nYour choice: ");
        if(scanf("%d",&user)!=1 || user<1 || user>3) 
        {
            fprintf(stderr,"Wrong choice\n");
            sleep(1.5);
        }
        clear_stdin();
        system("clear");
        switch(user)
        {
            case 1:
                ;
                size_t choice = 0;
                do
                {
                    printf("Basketball\n");
                    line();
                    printf("Menu:\n");
                    printf("1.Add a player\n2.Remove a player\n3.Add stats\n4.Top players\n5.Print player stats\n6.Print all players stats\n7.Exit\n");

                    printf("Type your choice: ");
                    if(scanf("%lu",&choice)!=1 || choice<1 || choice >7) 
                    {
                        fprintf(stderr,"Error occured.\n");
                        sleep(1);
                        clear_stdin();
                        choice = 0; //make it zero because we dont want switch to choose a case (previous value was saved!)
                    }

                    system("clear");
        

                    switch(choice)
                    {
                        case 1:
                            ;    
                            bool check = read_player(&ht,&vec);
                            if(!check)
                            {
                                fprintf(stderr,"Error occured.\n");
                                //FREE vector and hashtable
                                destroy(vec);
                                free_hashtable(ht);
                                return 1;
                            }
                            break;
                        case 2:
                            ;
                            if(!vec || !ht)
                            {
                                fprintf(stderr,"Error occured.\n");
                                sleep(1.5);
                                break;
                            }
                            bool check2 = remove_player(&ht,&vec);
                            if(!check2)
                            {
                                //FREE vector and hashtable
                               destroy(vec);
                                free_hashtable(ht);
                                fprintf(stderr,"Error occured.\n");
                                return 1;
                            }
                            break;
                        case 3: 
                            add_stats(ht);
                            break;
                        case 4:
                            //If the vector is empty there are no players 
                            if(empty(vec))
                            {
                                fprintf(stderr, "Team is empty. No players to display.\n");
                                sleep(2);
                                break;
                            }
                            label: 
                            ;
                            int stat = 0;
                            do
                            {
                                printf("Which statistic do you want to see the top 3 players?\n");
                                printf("1.Points\n2.Rebounds\n3.Assists\n4.Steals\n5.Blocks\n6.Turnovers\n7.Matches\n8.1p Percentage\n9.2p Percentage\n10.3p Percentage\n11.Exit\n");
                                printf("Type your choice: ");
                                if(scanf("%d",&stat)!=1 || stat<1 || stat>11)
                                {
                                    fprintf(stderr,"Wrong choice.\n");
                                    sleep(1.5);
                                    clear_stdin();
                                    system("clear");
                                    goto label; //We dont want to go back to the previous menu if there's a mistake from user
                                }
                                system("clear");
                                if(stat!=11)  
                                {
                                    print_top_players(vec,stat);
                                    system("clear");
                                }
                            }while(stat!=11);
                            break;
                        case 5:
                            ;
                            print_one_player(ht);
                            break;
                        case 6:
                            if (empty(vec)) 
                            {
                                printf("Team is empty. No players to display.\n");
                                sleep(2);
                                break;
                            }
                            clear_stdin();
                            printf("Type the name of the file: ");
                            char *filename = get_line();
                            if(!filename)
                            {
                                //FREE vector and hashtable
                                destroy(vec);
                                free_hashtable(ht);
                                fprintf(stderr,"Error occured.\n");
                                sleep(1.5);
                                return 1;
                            }
                            putchar('\n'); //for good visualization
                            print_all_players(vec,filename);
                            free(filename);
                            break;
                        }

                    system("clear");
                }while(choice!=7);
                destroy(vec);
                free_hashtable(ht);
                vec = NULL;
                ht = NULL;
                is_freed = true;
                break;
            case 2:
                ;
                if(!ht && !vec) 
                {
                    ht = create_hashtable(15);
                    vec = init(15);
                    is_freed = false;
                }
                bool test = load_file(&ht,&vec);
                if(!test)
                {
                    //FREE vector and hashtable
                    destroy(vec);
                    free_hashtable(ht);
                    fprintf(stderr,"Error occured.\n");
                    sleep(1.5);
                    return 1;
                }
                break;
        }
        system("clear");
    }while(user!=3);

    if(!is_freed)
    {
        destroy(vec);
        free_hashtable(ht);
    }
    return 0;
}