#include <stdio.h>
#include <stdlib.h>
#include "io.h"
#include "menu.h"

void show_main_menu(void)
{
     printf("1. New data\n2. Old data\n3. Exit\nYour choice: ");
}

void show_new_data_menu(void)
{
    printf("Basketball\n");
    line();
    printf("Menu:\n");
    printf("1.Add a player\n2.Remove a player\n3.Add stats\n4.Top players\n5.Print player stats\n6.Print all players stats\n7.Exit\n");
}


//Function to show the menu of the top-3 players case
void show_top_menu(void)
{
    printf("Which statistic do you want to see the top 3 players?\n");
    printf("1.Points\n2.Rebounds\n3.Assists\n4.Steals\n5.Blocks\n6.Turnovers\n7.Matches\n8.1p Percentage\n9.2p Percentage\n10.3p Percentage\n11.Exit\n");
}

//Function to deallocate the memory if there is an error
void error_handler(hashtable *ht,vector *vec)
{

    fprintf(stderr,"Error occured.\n");
    //FREE vector and hashtable
    destroy(vec);
    free_hashtable(ht);
    sleep(1.5);
    exit(1);
}