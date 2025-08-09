#include <stdlib.h>
#include <string.h>
#include "basket.h"
#include <unistd.h>
#include "avl.h"

/*Hidden struct from user*/
struct avl
{
    player *key;
    int height;
    struct avl *right;
    struct avl *left;
};

#define MAX(a, b) ((a) > (b) ? (a) : (b))

//Function that returns the height of a node in avl
int get_height(avl *node)
{
    if(!node) return 0;
    return node->height;
}

//Helper functions for rotations

//right rotation function
avl *right_rotation(avl *node)
{
    if (!node || !node->left) return node; 

    avl *l = node->left;
    avl *r = l->right;

    l->right = node;
    node->left = r;
    
    node->height = 1 + MAX(get_height(node->left),get_height(node->right));

    l->height = 1 + MAX(get_height(l->left),get_height(l->right));

    return l;
}

//left rotation function
avl *left_rotation(avl *node)
{
    if (!node || !node->right) return node; 

    avl *r = node->right;
    avl *l = r->left;

    r->left = node;
    node->right = l;
    
    node->height = 1 + MAX(get_height(node->left),get_height(node->right));

    r->height = 1 + MAX(get_height(r->left),get_height(r->right));

    return r;
}

//Function that searches a specific value in the avl tree
avl *search_avl(avl *root,char *val,Compare player_cmp)
{
    if(!root) return root;

    int cmp = player_cmp(val, root->key);
    if(!cmp) return root;

    if(cmp < 0) return search_avl(root->left, val,player_cmp);
    return search_avl(root->right, val,player_cmp );
}

//Function to get the balance factor of a node in avl
int balance_factor(avl *node)
{
    if(!node) return 0;

    return get_height(node->left) - get_height(node->right);
}

//Create a node in the avl tree
avl *create_avl(char *value,int size)
{
    avl *node = malloc(sizeof(avl));
    if(!node) return NULL;
    node->left = node->right = NULL;
    node->height = 1;
    //Allocate memory for the key
    node->key = calloc(1,size); // Initialize the key to zero
    if(!node->key) 
    {
        free(node);
        return NULL;
    }
    //Copy the value into the key
    char *name = copy(node->key,value);
    if(!name)
    {
        free(name);
        free(node->key);
        free(node); 
        return NULL;
    }

    return node;
}

//Function to insert a node in the avl tree
avl *insert_avl(avl **root, char *value, Compare player_cmp, int size)
{
    if (!(*root)) 
    {
        *root = create_avl(value, size);
        if (!(*root)) return NULL;
        return *root;
    }



    int cmp = player_cmp(value, (*root)->key);
    if (cmp < 0) (*root)->left = insert_avl(&(*root)->left, value, player_cmp, size);
    else if (cmp > 0) (*root)->right = insert_avl(&(*root)->right, value, player_cmp, size);
    else
        return *root; //Duplicates no available

    (*root)->height = 1 + MAX(get_height((*root)->left), get_height((*root)->right));

    int balance = balance_factor(*root);

    // Left Left case
    if (balance > 1 && player_cmp(value, (*root)->left->key) < 0) return right_rotation(*root);

    // Right Right case
    if (balance < -1 && player_cmp(value, (*root)->right->key) > 0) return left_rotation(*root);

    // Left Right case
    if (balance > 1 && player_cmp(value, (*root)->left->key) > 0) 
    {
        (*root)->left = left_rotation((*root)->left);
        return right_rotation(*root);
    }

    // Right Left case
    if (balance < -1 && player_cmp(value, (*root)->right->key) < 0) 
    {
        (*root)->right = right_rotation((*root)->right);
        return left_rotation(*root);
    }

    return *root;
}


//Helper function to find the in-order successor
avl *find_succ(avl *node)
{
    if(!node) return NULL;
    
    while(node->left) node = node->left;

    return node;
}

//Function to delete a node from the avl tree
avl *delete_avl(avl **root, char *value, Compare player_cmp, FreeFunc free_val)
{
    if (*root == NULL) return NULL;

    int cmp = player_cmp(value, (*root)->key);

    if (cmp < 0) (*root)->left = delete_avl(&(*root)->left, value, player_cmp, free_val);
    else if (cmp > 0) (*root)->right = delete_avl(&(*root)->right, value, player_cmp, free_val);
    else 
    {
        // Node with one or no child
        if (!(*root)->left || !(*root)->right) 
        {
            avl *temp = (*root)->left ? (*root)->left : (*root)->right;
            free_val((*root)->key);
            free(*root);
            *root = temp;
        }
        else 
        {
            // Node with two children
            avl *succ = find_succ((*root)->right);
            // Replace key with successor's key (but keep original memory)
            player *temp_key = (*root)->key;
            (*root)->key = succ->key;
            succ->key = temp_key;
            // Delete the successor
            (*root)->right = delete_avl(&(*root)->right, get_name(succ->key), player_cmp, free_val);
        }
    }

    if (*root == NULL) return NULL;

    // Update height
    (*root)->height = 1 + MAX(get_height((*root)->left), get_height((*root)->right));

    int balance = balance_factor(*root);

    // Rebalance the tree
    // Left Left case
    if (balance > 1 && balance_factor((*root)->left) >= 0) return right_rotation(*root);

    // Left Right case
    if (balance > 1 && balance_factor((*root)->left) < 0) 
    {
        (*root)->left = left_rotation((*root)->left);
        return right_rotation(*root);
    }

    // Right Right case
    if (balance < -1 && balance_factor((*root)->right) <= 0) return left_rotation(*root);

    // Right Left case
    if (balance < -1 && balance_factor((*root)->right) > 0) 
    {
        (*root)->right = right_rotation((*root)->right);
        return left_rotation(*root);
    }

    return *root;
}


// Function to print inorder traversal
void inorder(avl *avl,FILE *file)
{
    if(!avl || !avl->key) return;

    inorder(avl->left,file);

    char *name = get_name(avl->key);
    int points = get_points(avl->key);
    int rebounds = get_rebounds(avl->key);
    int ass = get_assists(avl->key);
    int steals = get_steals(avl->key);
    int blocks = get_blocks(avl->key); 
    int matches = get_matches(avl->key);
    int tos = get_tos(avl->key);

    printf("%-10s | %7d | %8d | %7d | %6d | %6d | %5d | %7d\n", 
           name, points, rebounds, ass, steals,
           blocks, tos, matches);


        fprintf(file, "%-10s | %-7d | %-8d | %-7d | %-6d | %-6d | %-5d | %-7d\n",
            name, points, rebounds, ass, steals,
            blocks, tos, matches);

    inorder(avl->right,file);
}

//Function to destroy all memory allocated for avl tree
void destroy_avl(avl **root,FreeFunc free_val)
{
    if(!(*root)) return;

    if((*root)->right) destroy_avl(&(*root)->right,free_val);
    if((*root)->left) destroy_avl(&(*root)->left,free_val);
    free_val((*root)->key); // Free the key
    free(*root);
    *root = NULL;
}



//Helper function to return a key of avl node
player *avl_val(avl *node)
{
    if(!node) return NULL;
    return node->key;
}