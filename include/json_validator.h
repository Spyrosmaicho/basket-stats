#ifndef JSON_VALIDATOR_H
#define JSON_VALIDATOR_H

#include <stdbool.h>
#include "hashtable.h"
#include "vector.h"
#include "team.h"

//The main function to check if the json file has the appropriate form
bool validate_json(hashtable **ht,vector **vec,team **t,char *json,char *mess);


#endif // JSON_VALIDATOR_H