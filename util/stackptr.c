#include <stdlib.h>
#include <stdio.h>
#include "stackptr.h"
#include "array_util.h"
#include "random.h"

struct stackptr *init_stackptr(struct stackptr *stk){
    stk->top = -1;
    stk->arr = (void **) malloc(sizeof(void *) * DEFAULT_STK_SIZE);
    if (stk->arr == NULL){
        return NULL;
    }
    stk->size = DEFAULT_STK_SIZE;
    return stk;
}

struct stackptr *reset_stackptr(struct stackptr *stk){
    free(stk->arr);
    return init_stackptr(stk);
}

void free_stackptr(struct stackptr *stk){
    free(stk->arr);
}

/**
 * If the stack is empty:       return = 1
 * If the stack is not empty:   return = 0
 */
int is_stackptr_empty(const struct stackptr *stk){
    if (stk->top == -1){
        return 1;
    }
    return 0;
}

void *top_ptr(const struct stackptr *stk){
    if (!is_stackptr_empty(stk)){
        return stk->arr[stk->top];
    }
    return NULL;
}

struct stackptr *push_ptr(struct stackptr *stk, void *ptr){
    if (stk->top == stk->size-1){
        stk->arr = resize_void_ptr_array(stk->arr, stk->size);
        stk->size *= RESIZE_FACTOR;
    }
    stk->arr[++stk->top] = ptr;
    return stk;
}

struct stackptr *pop_ptr(struct stackptr *stk){
    if (stk->top == -1){
        return NULL;
    }
    --stk->top;
}

void print_stackptr_state(struct stackptr *stk){
    printf("\nstack state:\n--> size = %i\n--> top = %i\n", 
        stk->size, stk->top);
}

void print_stackptr_test(struct stackptr *stk){
    if (stk->top == -1){
        printf("\nEmpty stack.\n");
        return;
    }
    while (stk->top >= 0){
        print_int_array((int *) stk->arr[stk->top], 2);
        free(stk->arr[stk->top]);
        pop_ptr(stk);
    }
}

void test_stackptr(){
    int size = 2, min = 1, max = 10, n = 11;
    struct stackptr stk;
    init_stackptr(&stk);

    for (int i = 0; i<n; ++i){
        push_ptr(&stk, (void *) get_rand_int_array(size, min, max));
        print_int_array((int *) stk.arr[i], size);
    }

    printf("\n\n");

    print_stackptr_test(&stk);

    if (pop_ptr(&stk) == NULL){
        printf("stack is empty no pop available.\n");
    }
}