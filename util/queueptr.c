#include "queueptr.h"
#include "util.h"
#include <stdlib.h>
#include <stdio.h>

struct queueptr *init_queueptr(struct queueptr *quptr){
    quptr->arr = (void **) malloc(sizeof(void *)*DEFAULT_QUEUE_SIZE);
    if (quptr->arr == NULL){
        printf("Error: allocation error in init_queueptr.\n");
        return NULL;
    }
    quptr->size = DEFAULT_QUEUE_SIZE;
    quptr->head = -1;
    quptr->tail = -1;
    return quptr;
}

struct queueptr *reset_queueptr(struct queueptr *quptr){
    free(quptr->arr);
    return init_queueptr(quptr);
}

void free_queueptr(struct queueptr *quptr){
    free(quptr->arr);
}

int is_queueptr_empty(const struct queueptr *quptr){
    if (quptr->head == -1){
        return 1;
    }
    return 0;
}

int is_queueptr_full(const struct queueptr *quptr){
    // if head == next tail
    if (quptr->head == (quptr->tail + 1) % quptr->size){
        return 1;
    }
    return 0;
}


/**
 * This function linearize the queue arr. If tail < head
 * it means that the tail of the queue is in the initial part of the 
 * array. Since a resize has been done now there is space to hold this 
 * portion of the queue after the head.
 * -> arr[0   tail   head   size-1]
 * -> arr[0   tail   head   size-1                 ]    // resize
 * -> arr[           head   size-1    tail         ]    // linearize
 */
static void linearize_arr(struct queueptr *quptr){
    if (quptr->tail < quptr->head){
        for (unsigned int i=0; i<=quptr->tail; ++i){
            quptr->arr[quptr->size + i] = quptr->arr[i];
        }
        quptr->tail = quptr->size + quptr->tail;
    }
}


struct queueptr *resize_queueptr(struct queueptr *quptr){
    void **new_arr = (void **) malloc(sizeof(void *)*quptr->size*QUEUE_RESIZE_FACTOR);
    if (new_arr == NULL){
        printf("Error: allocation in enqueue_int (resize).\n");
        return NULL;
    }
    for (unsigned int i=0; i<quptr->size; ++i){     // copy
        new_arr[i] = quptr->arr[i];
    }
    free(quptr->arr);
    quptr->arr = new_arr;
    linearize_arr(quptr);
    quptr->size *= QUEUE_RESIZE_FACTOR;
}

struct queueptr *enqueue_ptr(struct queueptr *quptr, void *ptr){
    if (is_queueptr_full(quptr)){
        if (resize_queueptr(quptr) == NULL){
            return NULL;
        }
    }
    if (quptr->head == -1){
        quptr->head = 0;
    }
    int next_tail = (quptr->tail+1)%quptr->size;
    quptr->arr[next_tail] = ptr;
    quptr->tail = next_tail;
    return quptr;
}

struct queueptr *dequeue_ptr(struct queueptr *quptr){
    if (is_queueptr_empty(quptr)){
        printf("Empty queue.\n");
        return NULL;
    }
    if (quptr->head == quptr->tail){
        quptr->tail = -1;
        quptr->head = -1;
    } else if (quptr->head == quptr->size-1){
        quptr->head = 0;
    } else {
        ++quptr->head;
    }
    return quptr;
}


void print_queueptr_state(struct queueptr *quptr){
    printf("\nqueueptr state:\narr  = %p\nsize = %i\nhead = %i\ntail = %i\n", 
        quptr->arr, quptr->size, quptr->head, quptr->tail);
    if (!is_queueptr_empty(quptr)){
        printf("head and tail values: [%p, %p]\n\n",
            quptr->arr[quptr->head], quptr->arr[quptr->tail]);
    } else {
        printf("head and tail values: [None, None]\n\n");
    }
}

