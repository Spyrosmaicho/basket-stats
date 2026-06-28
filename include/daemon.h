#ifndef DAEMON_H
#define DAEMON_H

#include <stdbool.h>
#include "hashtable.h"
#include "vector.h"
#include "team.h"

bool daemon_comm(hashtable **ht, vector **vec, team **t);


#endif