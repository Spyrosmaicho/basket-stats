#ifndef FILE_OP_H
#define FILE_OP_H

#include <stdbool.h>
#include "hashtable.h"
#include "vector.h"
#include "player.h"

//Function to get the file with the players 
bool load_txt_file(hashtable **ht,vector **vec,team **t,char *message);

bool load_json_file(hashtable **ht,vector **vec,team **t,char *message);

#endif