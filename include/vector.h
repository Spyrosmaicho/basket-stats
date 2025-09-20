#ifndef VECTOR_H
#define VECTOR_H

#include <stdbool.h>
#include <stddef.h>

typedef struct vector vector;

/*Function to check if the vector is empty*/
bool empty(vector *vec);

/*Function to initialize a dynamic array*/
vector  *init(int cap);

/*Function to insert an item into the dynamic array*/
void insert(vector *vec,void *item);

/*Function to return the last item of the dynamic array*/
void *peek(vector *vec);

/*Function to return how many elements the array has*/
int elements(vector *vec);

/*Function to get a specific value of the vector*/
void *get_value(vector *vec,int index);

/*Function to deallocate all the memory we allocated for the dynamic array*/
void destroy(vector *vec);

//Function to delete an item from the vector
void *vector_remove_by_item(vector *vec,void *item,int (*check_items)(void *elem,void *ctx));

//Function that finds an item in the vector and replace it with a new item
void vector_find_item(vector *vec,void *item,void *new_item);

//Function to sort the vector
void vector_sort(vector *vec,int (*cmp) (const void *,const void*));

//Function to return the biggest data of the vector
int vector_biggest_data(vector *vec,int (*val_ret)(void *));

//Helper functions
void *vec_data(vector *vec,int index);
int vec_index(vector *vec);

#endif