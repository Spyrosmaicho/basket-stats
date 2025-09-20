#ifndef HASHTABLE_H
#define HASHTABLE_H

#define LOAD_FACTOR 0.75

typedef struct hashnode hashnode;
typedef struct hashtable hashtable;

#include <stdbool.h>
#include <unistd.h>


//Function to create a new hashtable
hashtable *create_hashtable(size_t size);

//Function to insert a key-value pair into the hashtable.
void *insert_hash(struct hashtable *ht,const char *key,void *val);

//Function to search for a value by key in the hashtable
void *search_hash(const hashtable *ht,const char *key);

//Function to delete a key-value pair from the hashtable. Returns the value of the hashnode the needs to be freed
void *delete_hash(hashtable *ht,const char *key);

//Function to free the hashtable
void free_hashtable(hashtable *ht);

#endif 