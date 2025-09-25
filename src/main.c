#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "vector.h"
#include "hashtable.h"
#include "player.h"
#include "error.h"
#include "player_op.h"
#include "io.h"
#include "file_op.h"
#include "menu.h"
#include "new_data.h"
#include "file_data.h"
#include "team.h"

int main(void)
{
    //Create the hashtable and the vector for 15 players
    bool is_freed = false;
    hashtable *ht = create_hashtable(15);
    if(!ht) 
    {
        error_message("Memory allocation failed.\n");
        return 1;
    }
    vector *vec = init(15);
    if(!vec)
    {
        free_hashtable(ht);
        error_message("Memory allocation failed.\n");
        return 1;
    }
    team *t = create_team();
    if(!t)
    {
        free_hashtable(ht);
        destroy(vec);
        error_message("Memory allocation failed.\n");
        return 1;
    }
    int user = 0;
    do
    {
       show_main_menu();
        if(scanf("%d",&user)!=1 || user<1 || user>3) error_message("Wrong choice.\n");
        clear_stdin();
        system("clear");
        switch(user)
        {
            case 1: //add new data
                new_data(&ht,&vec,&t);
                if(vec) destroy(vec);
                if(ht) free_hashtable(ht);
                destroy_team(t);
                vec = NULL;
                ht = NULL;
                t = NULL;
                is_freed = true;
                break;
            case 2: //load data from a file
                file_data(&ht,&vec,&t,&is_freed);
                break;
        }
        system("clear");
    }while(user!=3);

    if(!is_freed)
    {
        destroy(vec);
        free_hashtable(ht);
        destroy_team(t);
    }
    return 0;
}