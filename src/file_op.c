#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "io.h"
#include "stat_type.h"
#include "add_stats.h"
#include "validate_stats.h"
#include "player_op.h"
#include "file_op.h"

//Function to get the file with the players 
bool load_file(hashtable **ht,vector **vec,team **t)
{
    printf("Type the name of the file: ");

    char *filename = get_line();
    if(!filename) return false;

    FILE *f = fopen(filename,"r");
    if(!f) 
    {
        free(filename);
        return false;
    }

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
        return 0;
    }

    if(buff[numCh-1] == '\n')
        buff[numCh-1] = '\0';

    free(buff);

    //READ THE DATA FROM THE FILE USING FSCANF. THEN INSERT THEM INTO THE hashtable and the vector
    char name[100];
    int off = 0,def = 0,ass = 0,steals=0,blocks=0,tos=0,matches=0,ft_made = 0,ft_attempted = 0,two_made = 0,two_attempted = 0,three_made = 0,three_attempted = 0,fouls =0;
    int res = 0;
    while((res = fscanf(f," %99[^|] | %d / %d | %d / %d | %d / %d | %d - %d | %d | %d | %d | %d | %d | %d",
        name,&ft_made,&ft_attempted,&two_made,&two_attempted,&three_made,&three_attempted,&off,&def,&ass,&steals,&blocks,&tos,&fouls,& matches)) == 15)
    {
        //We exclude the REBOUNDS because we dont need them in files
        int array_of_stats[STAT_COUNT-1] = {ft_made,ft_attempted,two_made,two_attempted,three_made,three_attempted,off,def,ass,steals,blocks,tos,fouls,matches};
        
        //We check that the data we get from the file are valid
        for(int i = 0;i<STAT_COUNT -1 ;i++)
        {
            if(!check_negative(array_of_stats[i])) 
            {
                fclose(f);
                return false;
            }
        }

        if(!check_pt(ft_made,ft_attempted) || !check_pt(two_made,two_attempted) || !check_pt(three_made,three_attempted)) 
        {
            fclose(f);
            return false;
        }

        //Every stat after REBOUNDS is at index - 2( = 1-indexed + we exclude REBOUNDS), those before are at index - 1
        if(array_of_stats[MATCHES-2]==0 && check_not_zero(array_of_stats,STAT_COUNT-1)) 
        {
            fclose(f);
            return false;
        }
        //Change the spaces in the end of the string with null
        int len = strlen(name);
        while (len > 0 && name[len - 1] == ' ') name[--len] = '\0';
        player *pl = create_player(name);

        insert_player_stats(pl,array_of_stats);
        add_all_player_stats(*t,pl);
        //Insert the player into the hashtable
        player *same = NULL;
        if((same = insert_hash(*ht,name,pl)))
        {
            vector_find_item(*vec,same,pl);
            delete_player(same); 
        }
        else insert(*vec,pl); //insert the player into the vector

    }
    if(res < 15 && res!=EOF) 
    {
        error_message("A stat is wrong.\n");
        fclose(f);
        return false;
    }
    fclose(f);

    return true;
}