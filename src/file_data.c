#include "io.h"
#include "file_op.h"
#include "file_data.h"

void file_data(hashtable **ht,vector **vec,team **t,bool *is_freed)
{
    if(!(*ht) && !(*vec) && !(*t)) 
    {
        *ht = create_hashtable(15);
        *vec = init(15);
        *t = create_team();
        *is_freed = false;
    }
    bool test = load_file(ht,vec,t);
    if(!test) error_handler(*ht,*vec,*t);
}