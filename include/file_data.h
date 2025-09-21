#ifndef FILE_DATA_H
#define FILE_DATA_H

#include <stdbool.h>
#include "hashtable.h"
#include "vector.h"
#include "team.h"

//Function to get data from a file
void file_data(hashtable **ht,vector **vec,team **t,bool *is_freed);

#endif