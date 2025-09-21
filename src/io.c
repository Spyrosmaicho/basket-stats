#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "player.h"
#include "io.h"

// Array of function pointers for sorting
int (*cmp_funcs[])(const void *, const void *) = 
{
    NULL, // Index 0 is unused for 1-based indexing
    cmp_points,
    cmp_rebs,
    cmp_ass,
    cmp_steals,
    cmp_blocks,
    cmp_tos,
    cmp_matches,
    cmp_ft_percent,
    cmp_two_percent,
    cmp_three_percent
};

//print header
void print_header(int len)
{
    printf("%-*s | %7s | %8s | %7s | %6s | %6s | %5s | %7s | %7s     | %7s     | %7s     | %6s | %6s | %6s\n",len,
    "Name", "Points", "Rebounds", "Assists", "Steals", "Blocks", "Tos", "Matches", "1pt"
    ,"2pt", "3pt","1pt %" ,"2pt %", "3pt %");
}

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

//Function to print the top 3 players according to user's choice
void print_top_players(vector *vec, int stat) 
{
    int len = vector_biggest_data(vec, player_name_len);

    // Sort the vector using the function pointer array
    vector_sort(vec, cmp_funcs[stat]);

    print_header(len);

    // Print first 3 players
    int num_players = (vec_index(vec) >= 3) ? 3 : vec_index(vec);
    for (int i = 0; i < num_players; i++) {
        print_player(vec_data(vec, i), NULL, len);
    }
    sleep(4);
}