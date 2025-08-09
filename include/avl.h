#ifndef AVL_H
#define AVL_H

#include <stdbool.h>
#include <stdio.h>
#include "player.h"
typedef struct avl avl;

typedef int (*Compare)(const void *a, const void *b);
typedef void (*FreeFunc)(void *);

//Function that searches a specific value in the avl tree
avl *search_avl(avl *root,char *val,Compare player_cmp);

//Function to insert a node in the avl tree
avl *insert_avl(avl **root, char *value, Compare player_cmp, int size);

//Function to delete a node from the avl tree
avl *delete_avl(avl **root,char *value,Compare player_cmp,FreeFunc free_val);

//Function that returns the height of a node in avl
int get_height(avl *node);

//Function to destroy all memory allocated for avl tree
void destroy_avl(avl **root,FreeFunc free_val);

// Function to print inorder traversal
void inorder(avl *avl,FILE *file);


//Helper function to return a key of avl node
player *avl_val(avl *node);

#endif