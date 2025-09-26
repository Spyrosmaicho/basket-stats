#include <stdlib.h>
#include <unistd.h>
#include "player.h"
#include "team.h"
#include "player_op.h"
#include "error.h"
#include "io.h"

// Array of function pointers for sorting
int (*cmp_funcs[])(const void *, const void *) = 
{
    NULL, // Index 0 is unused for 1-based indexing
    cmp_points,
    cmp_rebs,
    cmp_off_rebs,
    cmp_def_rebs,
    cmp_ass,
    cmp_steals,
    cmp_blocks,
    cmp_tos,
    cmp_fouls,
    cmp_matches,
    cmp_ft_percent,
    cmp_two_percent,
    cmp_three_percent
};

//print header
void print_player_header(int len,FILE *file)
{
    !file ? printf("%-*s | %7s | %17s| %7s | %6s | %6s | %5s | %7s | %7s | %7s     | %7s     | %7s     | %6s | %6s | %6s\n",len,
    "Name", "Points", "Rebounds(off/def)", "Assists", "Steals", "Blocks", "Tos","Fouls", "Matches", "1pt"
    ,"2pt", "3pt","1pt %" ,"2pt %", "3pt %") : fprintf(file,"%-*s | %7s | %17s| %7s | %6s | %6s | %5s | %7s| %7s | %7s     | %7s     | %7s     | %6s | %6s | %6s\n",len,
    "Name", "Points", "Rebounds(off/def)", "Assists", "Steals", "Blocks", "Tos","Fouls", "Matches", "1pt"
    ,"2pt", "3pt","1pt %" ,"2pt %", "3pt %");
    
}

//print team header
void print_team_header(FILE *file)
{
    !file ? printf("%-7s | %17s  | %7s | %6s | %6s | %5s | %7s | %7s | %7s     | %7s     | %7s     | %6s | %6s | %6s\n",
    "Points", "Rebounds(off/def)", "Assists", "Steals", "Blocks", "Tos","Fouls", "Matches", "1pt","2pt", "3pt","1pt %" ,"2pt %", "3pt %")
     : fprintf(file,"%-7s | %17s  | %7s | %6s | %6s | %5s | %7s | %7s | %7s     | %7s     | %7s     | %6s | %6s | %6s\n",
    "Points", "Rebounds(off/def)", "Assists", "Steals", "Blocks", "Tos","Fouls", "Matches", "1pt","2pt", "3pt","1pt %" ,"2pt %", "3pt %");
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
        error_message("Error occured.\n");
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

//Helper function to print the percentage
void print_percentage(const char *label,int made,int attempted,double percentage)
{
    printf("%s: %d / %d - %.2lf%%\n",label,made,attempted,attempted!= 0 ? percentage : 0.0);
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
        error_message("Player not found.\n");
        free(name);
        return;
    }
 
    system("clear");
    printf("Player: %s\n",get_name(player_found));
    line();
    printf("Points: %d\n",get_points(player_found));
    printf("Rebounds(off/def): %d (%d - %d)\n",get_rebounds(player_found),get_off_rebounds(player_found),get_def_rebounds(player_found));
    printf("Assists: %d\n",get_assists(player_found));
    printf("Steals: %d\n",get_steals(player_found));
    printf("Blocks: %d\n",get_blocks(player_found));
    printf("Turnovers: %d\n",get_tos(player_found));
    printf("Fouls: %d\n",get_fouls(player_found));
    printf("Matches: %d\n",get_matches(player_found));
    //Free throws percentage
    print_percentage("Free Throws - Percentage",get_ft_made(player_found),get_ft_attempted(player_found),get_1p_percentage(player_found));
    
    //Two points percentage
    print_percentage("Two Pointers - Percentage",get_two_made(player_found),get_two_attempted(player_found),get_2p_percentage(player_found));

    //Three points percentage
    print_percentage("Three Pointers - Percentage",get_three_made(player_found),get_three_attempted(player_found),get_3p_percentage(player_found));

    sleep(4);
    free(name);
}

//Function to print stats of all players
void print_all_players(vector *vec,char *txt,char *json)
{
    FILE *file_txt = fopen(txt, "w");
    if (!file_txt ) return;

    FILE *file_json = fopen(json,"w");
    if(!file_json)
    {
        fclose(file_txt);
        return;
    }
    int len = vector_biggest_data(vec,player_name_len);

    //Print the header to the terminal
    print_player_header(len,NULL);
    //Print the header to the txt file
    print_player_header(len,file_txt);

    //Print json file
    fprintf(file_json,"{\n\t\"players\":[\n\t");

    int numsSize = vec_index(vec);
    for(int i = 0;i<numsSize;i++)
    {
        player *pl = vec_data(vec,i);
        //Print the player to both txt file and terminal
        print_player(pl,file_txt,len);
        //Print json
        print_player_object(pl,file_json);
        if(i + 1 != numsSize) fprintf(file_json,",\n\t"); //Only the last value of json doesnt have ',' at the end
    }

    fprintf(file_json,"\n  ]\n}");

    sleep(4);
    fclose(file_txt);
    fclose(file_json);
}

//Function to print the top 3 players according to user's choice
void print_top_players(vector *vec, int stat) 
{
    int len = vector_biggest_data(vec, player_name_len);

    // Sort the vector using the function pointer array
    vector_sort(vec, cmp_funcs[stat]);

    print_player_header(len,NULL);

    // Print first 3 players
    int num_players = (vec_index(vec) >= 3) ? 3 : vec_index(vec);
    for (int i = 0; i < num_players; i++) print_player(vec_data(vec, i), NULL, len);
    sleep(4);
}

//Function to print the stats of the team
void print_team_stats(vector *vec,team *t,char *txt,char *json)
{   
     FILE *file_txt = fopen(txt, "w");
    if (!file_txt ) return;

    FILE *file_json = fopen(json,"w");
    if(!file_json) 
    {
        fclose(file_txt);
        return;
    }

    print_team_header(NULL);
    print_team_header(file_txt);

    //The number of matches the team has played is the biggest number of matches of a player among all the others
    int matches = vector_biggest_data(vec,player_match);
    set_team_matches(t,matches);

    print_team(t,NULL);
    print_team(t,file_txt);

    print_team_object(t,file_json);

    sleep(5);
    fclose(file_txt);
    fclose(file_json);
}