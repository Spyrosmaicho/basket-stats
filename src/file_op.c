#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "io.h"
#include "json_validator.h"
#include "json_parser.h"
#include "stat_type.h"
#include "add_stats.h"
#include "validate_stats.h"
#include "player_op.h"
#include "file_op.h"

//Index for the messages1 in order to access them easier and with better readability
typedef enum
{
    READ_FILE = 0,
    READ_LINE,
    NEGATIVE_STATS,
    INVALID_SHOTS,
    INVALID_FOULS,
    INVALID_MATCHES,
    READ_PLAYER,
    INVALID_FORMAT,
    READ_JSON,
    JSON_SYNTAX
}idx;

char *messages1[] = 
{
    "Could not read file\n",    
    "Could not read line.\n",
    "Stats are negative.\n",
    "Made shots cannot be more than attempted.\n",
    "Fouls are more than their valid value.\n",
    "It cant be simultaneously zero matches and positive stats\n",
    "Could not create player.\n",
    "The format of the file is invalid.\n",
    "Could not create Json.\n",
    "Json has invalid syntax.\n"
};

FILE *read_file(void)
{
    printf("Type the name of the file: ");

    char *filename = get_line();
    if(!filename) return NULL;

    FILE *f = fopen(filename,"r");
    if(!f) 
    {
        free(filename);
        return NULL;
    }

    //free filename (caller should free the returned string of get_line)
    free(filename);
    return f;
}

//Function to get the file with the players 
bool load_txt_file(hashtable **ht,vector **vec,team **t,char *message)
{
    FILE *f = read_file();
    if(!f) 
    {
        strcpy(message,messages1[READ_FILE]);
        return false;
    }
    //Read the first line of the file
    char *buff = NULL;
    size_t sizeAllocated = 0;
    ssize_t numCh = 0;
    if((numCh = getline(&buff, &sizeAllocated, f)) ==-1 )
    {
        strcpy(message,messages1[READ_LINE]);
        free(buff);
        fclose(f);
        return false;
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
                strcpy(message,messages1[NEGATIVE_STATS]);
                return false;
            }
        }

        if(!check_pt(ft_made,ft_attempted) || !check_pt(two_made,two_attempted) || !check_pt(three_made,three_attempted)) 
        {
            fclose(f);
            strcpy(message,messages1[INVALID_SHOTS]);
            return false;
        }

        if(array_of_stats[FOULS -2] > array_of_stats[MATCHES-2] * 5) //5 -> MAX FOULS FOR A GAME
        {
            strcpy(message,messages1[INVALID_FOULS]);
            fclose(f);
            return false;
        }

        //Every stat after REBOUNDS is at index - 2( = 1-indexed + we exclude REBOUNDS), those before are at index - 1
        if(array_of_stats[MATCHES-2]==0 && check_not_zero(array_of_stats,STAT_COUNT-1)) 
        {
            strcpy(message,messages1[INVALID_FOULS]);
            fclose(f);
            return false;
        }
        //Change the spaces in the end of the string with null
        int len = strlen(name);
        while (len > 0 && name[len - 1] == ' ') name[--len] = '\0';
        player *pl = create_player(name);
        if(!pl) 
        {
            strcpy(message,messages1[READ_PLAYER]);
            fclose(f);
            return false;
        }
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
        strcpy(message,messages1[INVALID_FORMAT]);
        fclose(f);
        return false;
    }
    fclose(f);

    return true;
}

//Function to insert stats from json file into our data structures
bool load_json_file(hashtable **ht,vector **vec,team **t,char *message)
{
    //We should close this file at the end of the function
    FILE *f = read_file();
    if(!f) 
    {
        strcpy(message,messages1[READ_FILE]);
        return false;
    }
    // Find the size of the file
    fseek(f, 0, SEEK_END);
    size_t filesize = ftell(f);
    rewind(f);

    // Create a buffer
    char *json = malloc(filesize + 1);
    if (!json) 
    { 
        strcpy(message,messages1[READ_JSON]);
        fclose(f); 
        return false; 
    }

    // Read all the file
    if(fread(json, 1, filesize, f)!=filesize) 
    {
        strcpy(message,messages1[READ_FILE]);
        free(json);
        fclose(f);
        return false;
    }
    json[filesize] = '\0';

    fclose(f);

    //After we should check that the format of the json is valid
    if(json_parser(json)) 
    {
        strcpy(message,messages1[JSON_SYNTAX]);
        free(json);
        return false;
    }
    //Next we must check that json has the aprropriate form to insert players
    if(!validate_json(ht,vec,t,json,message)) 
    {
        free(json);
        return false;
    }
    free(json);
    return true;
}