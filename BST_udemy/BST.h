#ifndef BST_H
#define BST_H

#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    char *data;
    struct node *left;
    struct node *right;
    int wordFreq;
}BstNode;

typedef struct BST{
    BstNode *root;
}BsTree;

#endif