#ifndef ERROR_H
#define ERROR_H

#include "hashtable.h"
#include "vector.h"
#include "team.h"

//Function to print a message for errors
void error_message(char *mes);

//Function to deallocate the memory if there is an error
void error_handler(hashtable *ht,vector *vec,team *t);

#endif