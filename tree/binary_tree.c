#include "binary_tree.h"
#include <stdlib.h>
#include <stdio.h>

struct binary_tree * create_node(int key){
    struct binary_tree *node = (struct binary_tree *) malloc(sizeof(struct binary_tree));
    if (node == NULL){
        printf("Errore in allocazione nodo.\n");
        return NULL;
    }
    node->key = key;
    node->sx = NULL;
    node->dx = NULL;
    return node;
}


void free_binary_tree(struct binary_tree *t){
    if (t != NULL){
        free_binary_tree(t->sx);
        free_binary_tree(t->dx);
        free(t);
    }
}


void preorder(struct binary_tree *t){
    if (t != NULL){
        printf("%i ", t->key);
        preorder(t->sx);
        preorder(t->dx);
    }
}


void inorder(struct binary_tree *t){
    if (t != NULL){
        preorder(t->sx);
        printf("%i ", t->key);
        preorder(t->dx);
    }
}


void postorder(struct binary_tree *t){
    if (t != NULL){
        preorder(t->sx);
        preorder(t->dx);
        printf("%i ", t->key);
    }
}


void breadth(struct binary_tree *t);