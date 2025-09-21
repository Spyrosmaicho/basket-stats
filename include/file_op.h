#ifndef FILE_OP_H
#define FILE_OP_H

#include <stdbool.h>
#include "hashtable.h"
#include "vector.h"
#include "player.h"

//Function to get the file with the players 
bool load_file(hashtable **ht,vector **vec);

#endif