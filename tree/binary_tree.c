#include "binary_tree.h"
#include "queueptr.h"
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

struct binary_tree *insert(struct binary_tree *t, int k){
    static int way_to_go = 0; 
    if (t != NULL){
        if (t->sx == NULL){
            t->sx = create_node(k);
            return t;
        } else if (t->dx == NULL){
            t->dx = create_node(k);
            return t;
        } else {
            if (way_to_go == 0){
                t->sx = insert(t->sx, k);
                way_to_go = 1;
            } else {
                t->dx = insert(t->dx, k);
                way_to_go = 0;
            }
            return t;
        }
    } else {
        return create_node(k);
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
        inorder(t->sx);
        printf("%i ", t->key);
        inorder(t->dx);
    }
}


void postorder(struct binary_tree *t){
    if (t != NULL){
        postorder(t->sx);
        postorder(t->dx);
        printf("%i ", t->key);
    }
}



void breadth(struct binary_tree *t){
    struct queueptr queue;
    init_queueptr(&queue);

    if (t != NULL){
        enqueue_ptr(&queue, (void *) t);
    }

    while (!is_queueptr_empty(&queue)){
        t = (struct binary_tree *) queue.arr[queue.head];
        if (t != NULL){
            printf("%i ", t->key);
            if (t->sx != NULL){
                enqueue_ptr(&queue, (void *) t->sx);
            }
            if (t->sx != NULL){
                enqueue_ptr(&queue, (void *) t->dx);
            }
            dequeue_ptr(&queue);
        } else {
            dequeue_ptr(&queue);
        }
    }
}

static void scroll_lv(struct queueptr *lv1, struct queueptr *lv2){
    static int lv = 0;
    struct binary_tree *t;
    while (!is_queueptr_empty(lv1)){
        t = (struct binary_tree *) lv1->arr[lv1->head];
        if (t != NULL){
            printf("%i ", t->key);
            enqueue_ptr(lv2, (void *) t->sx);
            enqueue_ptr(lv2, (void *) t->dx);
        } else {
            printf("-- ");
        }
        dequeue_ptr(lv1);
    }
    printf("\n");
}

void breadth_lvs(struct binary_tree *t){
    struct queueptr level1, level2, *lv1 = &level1, *lv2 = &level2;
    init_queueptr(lv1);
    init_queueptr(lv2);

    if (t != NULL){
        enqueue_ptr(lv1, (void *) t);
    }

    while (!is_queueptr_empty(lv1) || !is_queueptr_empty(lv2)){
        if (!is_queueptr_empty(lv1)){
            scroll_lv(lv1, lv2);
        } else {
            scroll_lv(lv2, lv1);
        }
    }
}