#include "stat_type.h"
#include "validate_stats.h"

#define MAX_FOULS 5

int made_shots(player *pl,int stat)
{
    switch(stat)
    {
        case 1: return get_ft_made(pl);
        case 3: return get_two_made(pl);
        case 5: return get_three_made(pl);
    }
    return 0;
}

int attempted_shots(player *p, int stat) 
{
    switch (stat) 
    {
        case 2: return get_ft_attempted(p);
        case 4: return get_two_attempted(p);
        case 6: return get_three_attempted(p);
    }
    return 0;
}

//Function to validate match, because we cant have for example 5 points and 0 matches
bool validate_match(player *pl,int value)
{
    return !(get_matches(pl)==0 && value>0);
}

//Function to validate fouls. Fouls cant be more than five
bool validate_foul(player *pl,int value)
{
    return !(get_fouls(pl) + value > MAX_FOULS);
}

//Function to validate made, attempted shots
bool validate_shots(player *pl,int stat,int value)
{
    int made =  0,attempts = 0;
    if(stat % 2 == 1) //Made shots
    {
        made = made_shots(pl,stat) + value;
        attempts = attempted_shots(pl,stat+1);
    }
    else //Attempted shots
    {
        attempts = attempted_shots(pl,stat) + value;
        made = made_shots(pl,stat-1);
    }

    return !(made > attempts);
}

//Function to validate rebounds
bool validate_rebs(player *pl,int stat,int value,int *total,int *off,int *def)
{
    *total = get_rebounds(pl);
    if(stat==OFF_REBOUNDS) *off = get_off_rebounds(pl) + value;
    else *def = get_def_rebounds(pl) + value;


    return !(*off > *total || *def > *total);
}

//Function to check made-attempted
bool check_pt(int made,int attempted)
{
    return !(made > attempted);
}

//Function to check that all the stats are positive
bool check_negative(int val)
{
    return !(val<0);
}

//Function to check that all the stats are zero or not
bool check_not_zero(int *array,int numsSize)
{
    for(int i = 0;i<numsSize;i++)
    {
        if(array[i]!=0) return true;
    }

    return false;
}