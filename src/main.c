#include "basket.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "avl.h"

int main(void)
{
    int user = 0;
    avl *avl = NULL;
    do
    {
        printf("1. New data\n2. Old data\n3. Exit\nYour choice: ");
        if(scanf("%d",&user)!=1) 
        {
            fprintf(stderr,"Wrong choice\n");
            sleep(1);
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
                    printf("1.Add a player\n2.Remove a player\n3.Add stats\n4.Print player stats\n5.Print team stats\n6.Exit\n");

                    printf("Type your choice: ");
                    if(scanf("%lu",&choice)!=1) 
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
                            bool check = read_player(&avl);
                            if(!check)
                            {
                                fprintf(stderr,"Error occured.\n");
                                //FREE avl TREE
                                destroy_avl(&avl,free_val);
                                return 1;
                            }
                            break;
                        case 2:
                            ;
                            if(!avl)
                            {
                                fprintf(stderr,"Error occured.\n");
                                sleep(1.5);
                                break;
                            }
                            bool check2 = rem(&avl);
                            if(!check2)
                            {
                                //FREE avl TREE
                                destroy_avl(&avl,free_val);
                                fprintf(stderr,"Error occured.\n");
                                return 1;
                            }
                            break;
                        case 3: 
                            add_stats(avl);
                            break;
                        case 4:
                            print_stats(avl);
                            break;
                        case 5:
                            if (!avl) 
                            {
                                printf("Team is empty. No players to display.\n");
                                sleep(2);
                                break;
                            }
                            clear_stdin();
                            printf("Type the name of the file: ");
                            char *filename = get_func();
                            if(!filename)
                            {
                                destroy_avl(&avl,free_val);
                                fprintf(stderr,"Error occured.\n");
                                sleep(1.5);
                                return 1;
                            }
                            putchar('\n'); //for good visualization
                            print_team(avl,filename);
                            free(filename);
                            break;
                        }

                    system("clear");
                }while(choice!=6);


                //Finish the program and deallocate all the memory
                destroy_avl(&avl,free_val);
                break;
            case 2:
                avl = load_file(avl);
                if(!avl)
                {
                    fprintf(stderr,"Error occured.\n");
                    sleep(1.5);
                }
                break;
        }
        system("clear");
    }while(user!=3);
    destroy_avl(&avl,free_val);
    return 0;
}