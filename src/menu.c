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
    printf("1.Add a player\n2.Remove a player\n3.Add stats\n4.Top players\n5.Print player stats\n6.Print all players stats\n7.Print team stats\n8.Exit\n");
}

void show_file_menu(void)
{
    printf("1.Txt File\n");
    printf("2.Json File\n");
    printf("3.Exit\n");
}

//Function to show the menu of the top-3 players case
void show_top_menu(void)
{
    printf("Which statistic do you want to see the top 3 players?\n");
    printf("1.Points\n");
    printf("2.Total Rebounds\n");
    printf("3.Offensive Rebounds\n");
    printf("4.Defensive Rebounds\n");
    printf("5.Assists\n");
    printf("6.Steals\n");
    printf("7.Blocks\n");
    printf("8.Turnovers\n");
    printf("9.Fouls\n");
    printf("10.Matches\n");
    printf("11.1p Percentage\n");
    printf("12.2p Percentage\n");
    printf("13.3p Percentage\n");
    printf("14.Exit\n");
}

void add_stats_menu(void)
{
    printf("Which stat you want to change: \n");
 
    printf("1.1p Made\n");
    printf("2.1p Attempted\n");
    printf("3.2p Made\n");
    printf("4.2p Attempted\n");
    printf("5.3p Made\n");
    printf("6.3p Attempted\n");
    printf("7.Total Rebounds\n");
    printf("8.Offensive Rebounds\n");
    printf("9.Defensive Rebounds\n");
    printf("10.Assists\n");
    printf("11.Steals\n");
    printf("12.Blocks\n");
    printf("13.Turnovers\n");
    printf("14.Fouls\n");
    printf("15.Matches\n");
    printf("16.Exit\n");
}