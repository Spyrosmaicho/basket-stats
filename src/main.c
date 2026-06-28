#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "daemon.h"
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

int main(int argc, char **argv)
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


    if(argc == 1) {
        error_message("More arguments!\nTry again using --help");
        goto free;
    }
    else if(argc > 1 && strcmp(argv[1],"--daemon" )!=0 && strcmp(argv[1],"--interactive" )!=0 && strcmp(argv[1],"--help" )!=0){
        error_message("Wrong Argument!\nTry again using --help");
        goto free;
    }
    else if(argc > 1 && strcmp(argv[1],"--help" )== 0){
        error_message("1) ./basket --daemon\n2) ./basket --interactive\n");
        goto free;
    }
    else if (argc > 1 && strcmp(argv[1], "--daemon") == 0) {
        bool is_ok = daemon_comm(&ht,&vec,&t);
        if(!is_ok) {
            error_message("Problem occured.\n");    
        }
        goto free;
    }
    else if(argc > 1 && strcmp(argv[1],"--interactive" )==0){
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
    }

free:
    if(!is_freed)
    {
        destroy(vec);
        free_hashtable(ht);
        destroy_team(t);
    }
    return 0;
}