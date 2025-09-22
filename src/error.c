#include <stdio.h>
#include <stdlib.h>
#include "error.h"

//Function to print a message for errors
void error_message(char *mes)
{
    fprintf(stderr,"%s",mes);
    sleep(1.5);
}

//Function to deallocate the memory if there is an error
void error_handler(hashtable *ht,vector *vec,team *t)
{
    //FREE vector and hashtable
    destroy(vec);
    free_hashtable(ht);
    destroy_team(t);
    error_message("Error occured.\n");
    exit(1);
}