#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "vector.h"
#include "hashtable.h"
#include "player.h"
#include "player_op.h"
#include "io.h"
#include "file_op.h"
#include "menu.h"
#include "new_data.h"
#include "file_data.h"


int main(void)
{
    //Create the hashtable and the vector for 15 players
    bool is_freed = false;
    hashtable *ht = create_hashtable(15);
    vector *vec = init(15);
    int user = 0;
    do
    {
       show_main_menu();
        if(scanf("%d",&user)!=1 || user<1 || user>3) 
        {
            fprintf(stderr,"Wrong choice\n");
            sleep(1.5);
        }
        clear_stdin();
        system("clear");
        switch(user)
        {
            case 1:
                new_data(ht,vec);
                destroy(vec);
                free_hashtable(ht);
                vec = NULL;
                ht = NULL;
                is_freed = true;
                break;
            case 2:
                file_data(ht,vec,&is_freed);
                break;
        }
        system("clear");
    }while(user!=3);

    if(!is_freed)
    {
        destroy(vec);
        free_hashtable(ht);
    }
    return 0;
}