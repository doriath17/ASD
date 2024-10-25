#include <stdlib.h>
#include <stdio.h>
#include "avl.h"
#include "queueptr.h"

struct avl_tree * create_avl_node(int key){
    struct avl_tree *node = (struct avl_tree *) malloc(sizeof(struct avl_tree));
    if (node == NULL){
        printf("Errore in allocazione nodo.\n");
        return NULL;
    }
    node->key = key;
    node->h   = 0;
    node->sx  = NULL;
    node->dx  = NULL;
    return node;
}

void free_avl_tree(struct avl_tree *avl){
    if (avl != NULL){
        free_avl_tree(avl->sx);
        free_avl_tree(avl->dx);
        free(avl);
    }
}

void inorder_avl(struct avl_tree *avl){
    if (avl != NULL){
        inorder_avl(avl->sx);
        printf("%i ", avl->key);
        inorder_avl(avl->dx);
    }
}

static void scroll_lvs_avl(struct queueptr *lv1, struct queueptr *lv2){
    static int lv = 0;
    struct avl_tree *avl;
    while (!is_queueptr_empty(lv1)){
        avl = (struct avl_tree *) lv1->arr[lv1->head];
        if (avl != NULL){
            printf("%i ", avl->key);
            enqueue_ptr(lv2, (void *) avl->sx);
            enqueue_ptr(lv2, (void *) avl->dx);
        } else {
            printf("-- ");
        }
        dequeue_ptr(lv1);
    }
    printf("\n");
}

void breadth_lvs_avl(struct avl_tree *avl){
    struct queueptr level1, level2, *lv1 = &level1, *lv2 = &level2;
    init_queueptr(lv1);
    init_queueptr(lv2);

    if (avl != NULL){
        enqueue_ptr(lv1, (void *) avl);
    }

    while (!is_queueptr_empty(lv1) || !is_queueptr_empty(lv2)){
        if (!is_queueptr_empty(lv1)){
            scroll_lvs_avl(lv1, lv2);
        } else {
            scroll_lvs_avl(lv2, lv1);
        }
    }
}