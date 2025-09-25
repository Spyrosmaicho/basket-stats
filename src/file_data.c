#include <stdio.h>
#include <stdlib.h>
#include "io.h"
#include "menu.h"
#include "error.h"
#include "file_op.h"
#include "file_data.h"

void file_data(hashtable **ht,vector **vec,team **t,bool *is_freed)
{
    char message[100]="\0";//Enough for the messages we want to print
    if(!(*ht) && !(*vec) && !(*t)) 
    {
        *ht = create_hashtable(15);
        *vec = init(15);
        *t = create_team();
        *is_freed = false;
    }
    int choice = 0;
    do
    {
        show_file_menu();
        printf("Type your choice: ");
        if(scanf("%d",&choice)!=1 || choice <1 || choice >3)
        {
            error_message("Wrong choice\n");
            system("clear");
            clear_stdin();
        }
        switch(choice)
        {
            case 1:
                clear_stdin();
                system("clear");
                if(!load_txt_file(ht,vec,t,message)) error_handler(*ht,*vec,*t,message);
                break;
            case 2: 
                clear_stdin();
                system("clear");
                if(!load_json_file(ht,vec,t,message)) error_handler(*ht,*vec,*t,message);
                break;
        }
        system("clear");
    }while(choice!=3);
}
