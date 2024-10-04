#include "queueint.h"
#include "util.h"
#include <stdlib.h>
#include <stdio.h>

struct queueint *init_queueint(struct queueint *quint){
    quint->arr = (int *) malloc(sizeof(int)*DEFAULT_QUEUE_SIZE);
    if (quint->arr == NULL){
        printf("Error: allocation error in init_queueint.\n");
        return NULL;
    }
    quint->size = DEFAULT_QUEUE_SIZE;
    quint->head = -1;
    quint->tail = -1;
    return quint;
}

struct queueint *reset_queueint(struct queueint *quint){
    free(quint->arr);
    return init_queueint(quint);
}

void free_queueint(struct queueint *quint){
    free(quint->arr);
}

int is_queueint_empty(const struct queueint *quint){
    if (quint->head == -1){
        return 1;
    }
    return 0;
}

int is_queueint_full(const struct queueint *quint){
    // if head == next tail
    if (quint->head == (quint->tail + 1) % quint->size){
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
static void linearize_arr(struct queueint *quint){
    if (quint->tail < quint->head){
        for (unsigned int i=0; i<=quint->tail; ++i){
            quint->arr[quint->size + i] = quint->arr[i];
        }
        quint->tail = quint->size + quint->tail;
    }
}


struct queueint *resize_queueint(struct queueint *quint){
    int *new_arr = (int *) malloc(sizeof(int)*quint->size*QUEUE_RESIZE_FACTOR);
    if (new_arr == NULL){
        printf("Error: allocation in enqueue_int (resize).\n");
        return NULL;
    }
    for (unsigned int i=0; i<quint->size; ++i){     // copy
        new_arr[i] = quint->arr[i];
    }
    free(quint->arr);
    quint->arr = new_arr;
    linearize_arr(quint);
    quint->size *= QUEUE_RESIZE_FACTOR;
}

struct queueint *enqueue_int(struct queueint *quint, int k){
    if (is_queueint_full(quint)){
        if (resize_queueint(quint) == NULL){
            return NULL;
        }
    }
    if (quint->head == -1){
        quint->head = 0;
    }
    int next_tail = (quint->tail+1)%quint->size;
    quint->arr[next_tail] = k;
    quint->tail = next_tail;
    return quint;
}

struct queueint *dequeue_int(struct queueint *quint){
    if (is_queueint_empty(quint)){
        printf("Empty queue.\n");
        return NULL;
    }
    if (quint->head == quint->tail){
        quint->tail = -1;
        quint->head = -1;
    } else if (quint->head == quint->size-1){
        quint->head = 0;
    } else {
        ++quint->head;
    }
    return quint;
}


void print_queueint_state(struct queueint *quint){
    printf("\nqueueint state:\narr  = %p\nsize = %i\nhead = %i\ntail = %i\n", 
        quint->arr, quint->size, quint->head, quint->tail);
    if (!is_queueint_empty(quint)){
        printf("head and tail values: [%i, %i]\n\n",
            quint->arr[quint->head], quint->arr[quint->tail]);
    } else {
        printf("head and tail values: [None, None]\n\n");
    }
}

void print_queueint(struct queueint *quint){
    printf("queueint:\n");
    if (is_queueint_empty(quint)){
        printf("queue is empty.\n");
    } else {
        if (quint->tail < quint->head){
            for (unsigned int i=quint->head; i<=quint->size-1; ++i){
                printf("%i ", quint->arr[i]);
            }
            for (unsigned int i=0; i<=quint->tail; ++i){
                printf("%i ", quint->arr[i]);
            }
        } else {
            for (unsigned int i=quint->head; i<=quint->tail; ++i){
                printf("%i ", quint->arr[i]);
            }
        }
        printf("\n");
    }
}

void print_queueint_repr(struct queueint *quint){
    printf("queueint:\n");
    if (is_queueint_empty(quint)){
        printf("queue is empty.\n");
    } else {
        for (unsigned int i=0; i<quint->size; ++i){
            if (quint->tail < quint->head){
                if (i <= quint->tail || i >= quint->head){
                    printf("%i ", quint->arr[i]);
                } else {
                    printf("0 ");
                }
            } else {
                if (i >= quint->head && i <= quint->tail){
                    printf("%i ", quint->arr[i]);
                } else {
                    printf("0 ");
                }
            }
        }
        printf("\n");
    }
}

