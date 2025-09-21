#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "io.h"
#include "file_op.h"

//Function to get the file with the players 
bool load_file(hashtable **ht,vector **vec)
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
    int off = 0,def = 0,ass = 0,steals=0,blocks=0,tos=0,matches=0,ft_made = 0,ft_attempted = 0,two_made = 0,two_attempted = 0,three_made = 0,three_attempted = 0;
    int res = 0;
    while((res = fscanf(f," %99[^|] | %d / %d | %d / %d | %d / %d | %d - %d | %d | %d | %d | %d | %d",
        name,&ft_made,&ft_attempted,&two_made,&two_attempted,&three_made,&three_attempted,&off,&def,&ass,&steals,&blocks,&tos,& matches)) == 14)
    {
        //This cannot happen. It's not true
        if(two_made > two_attempted || three_made > three_attempted || ft_made>ft_attempted) 
        {
            fclose(f);
            return false;
        }
        //Change the spaces in the end of the string with null
        int len = strlen(name);
        while (len > 0 && name[len - 1] == ' ') name[--len] = '\0';
        player *pl = create_player(name);

        int array_of_stats[13] = {ft_made,two_made,three_made,ft_attempted,two_attempted,three_attempted,off,def,ass,steals,blocks,tos,matches};
        insert_player_stats(pl,array_of_stats);

        //Insert the player into the hashtable
        player *same = NULL;
        if((same = insert_hash(*ht,name,pl)))
        {
            vector_find_item(*vec,same,pl);
            delete_player(same); 
        }
        else insert(*vec,pl); //insert the player into the vector

    }
    if(res < 12 && res!=EOF) 
    {
        error_message("A stat is wrong.\n");
        fclose(f);
        return false;
    }
    fclose(f);
    return true;
}