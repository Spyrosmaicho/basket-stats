#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "vector.h"
#include "player.h"

struct vector
{
    void **data;
    int capacity;
    int index;
    void (*free_func)(void*);
};

/*Function to initialize a dynamic array*/
vector  *init(int cap)
{
    vector *vec = malloc(sizeof(struct vector));
    if(!vec) return NULL;
    vec->capacity = cap;
    //Initialize every player
    vec->data = malloc( sizeof(void*) * cap);
    if(!vec->data) 
    {
        free(vec);
        return NULL;
    }
    vec->index = 0;
    vec->free_func = delete_player;
    return vec;
}

/*Function to check if the vector is empty*/
bool empty(vector *vec)
{
    return vec->index == 0;
}

/*Function to check if the vector is full*/
bool full(vector *vec)
{
    return vec->capacity == vec->index;
}

/*Function to return how many elements the vector has*/
int elements(vector *vec)
{
    return vec->index;
}

/*Function to insert an item into the dynamic array*/
void insert(vector *vec,void *item)
{
    if(full(vec))
    {
        vec->capacity *=2;
        vec->data = realloc(vec->data,vec->capacity *sizeof(void*));
        assert(vec->data);
    }
    vec->data[vec->index++] = item;
}

/*Function to get a specific value of the vector*/
void *get_value(vector *vec,int index)
{
    return vec->index > index ? vec->data[index] : NULL;
}

/*Function to return the last item of the dynamic array*/
void *peek(vector *vec)
{
    return vec->index ? vec->data[vec->index-1] : NULL;
}


//Function to delete an item from the vector
void *delete(vector *vec,int index)
{
    assert(vec->index > index);
    void *ret = vec->data[index];
    memmove(vec->data+index,vec->data+index+1,(vec->index-- - index)*sizeof(void*));

    return ret;
}

/*Function to deallocate all the memory we allocated for the dynamic array*/
void destroy(vector *vec)
{
    for(int i = 0;i<vec->index;i++) vec->free_func(vec->data[i]);

    free(vec->data);
    vec->data = NULL;
    free(vec);
}

void *vector_remove_by_item(vector *vec,void *item,int (*check_items)(void *item,void *elem))
{
    for (int i = 0; i < vec->index; i++) 
    {
        if (check_items(vec->data[i],item)) {
        
            void *to_delete = delete(vec, i);

            return to_delete;
        }
    }
    return NULL; 
}

void vector_find_item(vector *vec,void *item,void *new_item)
{
    for(int i = 0;i<vec->index;i++)
    {
        if(vec->data[i]==item) 
        {
            vec->data[i] = new_item;
            break;
        }
    }
}

void *vec_data(vector *vec,int index)
{
    return vec->data[index];
}

int vec_index(vector *vec)
{
    return vec->index;
}


void vector_sort(vector *vec,int (*cmp) (const void *,const void*))
{
    qsort(vec->data,vec->index,sizeof(void*),cmp);
}


int vector_biggest_data(vector *vec,int (*val_ret)(void *))
{
    int max = -1;
    for(int i = 0;i<vec->index;i++)
    {
        int len = val_ret(vec->data[i]);
        if(len > max) max = len;
    }

    return max;
}
