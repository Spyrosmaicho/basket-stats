#include <string.h>
#include <stdlib.h>
#include "stat_type.h"
#include "add_stats.h"
#include "json_parser.h"
#include "validate_stats.h"
#include "player.h"
#include "json_validator.h"

const char *required_fields[] = {
    "\"Name\"", "\"FT_Made\"", "\"FT_Attempted\"", "\"Two_Made\"", "\"Two_Attempted\"",
    "\"Three_Made\"", "\"Three_Attempted\"", "\"Off_Rebounds\"", "\"Def_Rebounds\"",
    "\"Assists\"", "\"Steals\"", "\"Blocks\"", "\"Turnovers\"", "\"Fouls\"", "\"Matches\""
};
#define NUM_FIELDS (int)(sizeof(required_fields)/sizeof(required_fields[0]))

typedef enum{
    PLAYERS_FIELD = 0,
    PLAYERS_FORMAT,
    READ_PLAYER_OBJECT,
    CREATE_PLAYER,
    NAME_STRING,
    NUMBER,
    NEGATIVE_STATS,
    INVALID_SHOTS,
    INVALID_FOULS,
    INVALID_MATCHES,
}idx;

char *messages2[] = 
{
    "Players field not found.\n",
    "Players format is invalid.\n",
    "Could not allocate memory for player object.\n",
    "Could not create a player.\n",
    "Name value is not a string.\n",
    "Number is not valid.\n",
    "Stats are negative.\n",
    "Made shots cannot be more than attempteds.\n",
    "Fouls are more than their valid value.\n",
    "It cant be simultaneously zero matches and positive stats\n"
};

//Function to return if the field "player" is in the file.
char *find(char *json,const char *delem)
{
    return strstr(json, delem);
}

char* find_object_end(char *start) 
{
    int depth = 0;
    char *p = start;

    if (*p != '{') return NULL;
    depth = 1;
    p++;

    while (*p && depth > 0) 
    {
        if (*p == '{') depth++;
        else if (*p == '}') depth--;
        p++;
    }

    if (depth == 0) return p - 1;
    return NULL; 
}
bool find_every_field(hashtable **ht,vector **vec,team **t,char *arr_str,char *mess)
{
    int values[NUM_FIELDS-1]; //Everything except name
    char *p;
    player *pl = NULL;
    char name_buf[100] = "\0";
    for(int i = 0; i < NUM_FIELDS; i++) 
    {
        p = find(arr_str, required_fields[i]);
        if(!p) 
        {
            sprintf(mess,"Could not find %s field.\n",required_fields[i]);
            if(i >0) delete_player(pl);
            return false;
        }
        p += strlen(required_fields[i]);
        skip_space(&p);
        if(*p != ':')
        {
            strcpy(mess,messages2[PLAYERS_FORMAT]);
            return false;
        }
        p++;
        skip_space(&p);
        // Name
       if(strcmp(required_fields[i], "\"Name\"") == 0)
        { 
            if(*p != '\"') 
            {
                strcpy(mess,messages2[NAME_STRING]);
                return false;
            }
            p++;
            char *q = strchr(p, '\"');
            if(!q) 
            {
                strcpy(mess,messages2[NAME_STRING]);
                return false;
            }
            int len = q - p;
            if(len >= (int)sizeof(name_buf)) len = sizeof(name_buf)-1; //Ensure we avoid buffer overflow
            snprintf(name_buf, sizeof(name_buf), "%.*s", len, p);
            // Create player with name_buf
            pl = create_player(name_buf);
            if(!pl)
            {
                strcpy(mess,messages2[CREATE_PLAYER]);
                return false;
            }
        } 
        //Stats
        else    
        { 
            char *end;
            int val = (int)strtol(p, &end, 10);
            if (p == end) 
            {
                delete_player(pl);
                snprintf(mess,100,"%s value is not a number.\n",required_fields[i]);
                return false;        //No number
            }
            if (*end != '\0' && *end != ',' && *end != '}' && *end != ' ' && *end!= '\n' && *end != '\t') 
            {
                delete_player(pl);
                strcpy(mess,messages2[NUMBER]);
                return false;
            }
            values[i-1] = val;
        }
    }
    //We check that the data we get from the file are valid
    for(int i = 0;i<NUM_FIELDS-1 ;i++)
    {
        if(!check_negative(values[i])) 
        {
            delete_player(pl);
            strcpy(mess,messages2[NEGATIVE_STATS]);
            return false;
        }
    }

    if(!check_pt(values[FT_MADE-1],values[FT_ATTEMPTED-1]) || 
    !check_pt(values[TWO_MADE-1],values[TWO_ATTEMPTED-1]) || !check_pt(values[THREE_MADE-1],values[THREE_ATTEMPTED-1])) 
    {
        delete_player(pl);
        strcpy(mess,messages2[INVALID_SHOTS]);
        return false;
    }    

    if(values[FOULS -2] > values[MATCHES-2] * 5) //5 -> MAX FOULS FOR A GAME
    {
        delete_player(pl);
        strcpy(mess,messages2[INVALID_FOULS]);
        return false;
    }

    //Every stat after REBOUNDS is at index - 2( = 1-indexed + we exclude REBOUNDS), those before are at index - 1
    if(values[MATCHES-2]==0 && check_not_zero(values,NUM_FIELDS-1)) 
    {
        delete_player(pl);
        strcpy(mess,messages2[INVALID_MATCHES]);
        return false;
    }

    //Then we insert the values into the data structures
    insert_player_stats(pl,values);
    add_all_player_stats(*t,pl);
    //Insert the player into the hashtable
    player *same = NULL;
    if((same = insert_hash(*ht,name_buf,pl)))
    {
        vector_find_item(*vec,same,pl);
        delete_player(same); 
    }
    else insert(*vec,pl); //insert the player into the vector
    return true;
}

//The main function to check if the json file has the appropriate form
bool validate_json(hashtable **ht,vector **vec,team **t,char *json,char *mess)
{
    char *str = find(json,"\"players\""); 
    if(!str) 
    {
        strcpy(mess,messages2[PLAYERS_FIELD]); 
        return false; //We didnt find that field.
    }
    //We skip now the field players
    int len = strlen("\"players\"");
    str += len;
    //Skip ":"
    skip_space(&str);
    if(*str != ':')
    {
        strcpy(mess,messages2[PLAYERS_FORMAT]);
        return false;
    }
    str++;
    //Skip "["
    skip_space(&str);
    if(*str != '[') 
    {
        strcpy(mess,messages2[PLAYERS_FORMAT]);
        return false; //Should be array
    }
    str++;
    //Its valid if the array is empty
    skip_space(&str);
    if(*str == ']') return true;
    //Skip "{"
    do
    {
        skip_space(&str);
        if(*str != '{') 
        {
            strcpy(mess,messages2[PLAYERS_FORMAT]);
            return false;
        }
        char *start = str; //Hold the start of the object
        char *end = find_object_end(start);
        if(!end) 
        {
            strcpy(mess,messages2[PLAYERS_FORMAT]);
            return false;
        }
        char *arr_str = malloc(end - start +1);
        if(!arr_str)
        {
            strcpy(mess,messages2[READ_PLAYER_OBJECT]);
            return false;
        }
        memcpy(arr_str, start, end -start);
        arr_str[end-start] = '\0';
        //Now we should check every field we need
        if(!find_every_field(ht,vec,t,arr_str,mess)) 
        {
            free(arr_str);
            return false;
        }
        free(arr_str);
        str = end;
        str++; //Because the end points exactly to '}'
        skip_space(&str);
        if(*str == ',') str++;
    }while(*str != ']');

    return true;
}