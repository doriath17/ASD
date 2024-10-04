#include <stdlib.h>
#include <stdio.h>
#include "stackint.h"
#include "array_util.h"
#include "random.h"

struct stackint *init_stackint(struct stackint *stk){
    stk->top = -1;
    stk->arr = get_int_array(DEFAULT_STK_SIZE);
    if (stk->arr == NULL){
        return NULL;
    }
    stk->size = DEFAULT_STK_SIZE;
    return stk;
}

struct stackint *reset_stackint(struct stackint *stk){
    free(stk->arr);
    return init_stackint(stk);
}

void free_stackint(struct stackint *stk){
    free(stk->arr);
}

int is_stackint_empty(const struct stackint *stk){
    if (stk->top == -1){
        return 1;
    }
    return 0;
}

int top_int(const struct stackint *stk){
    if (!is_stackint_empty(stk)){
        return stk->arr[stk->top];
    }
    return -1;
}

struct stackint *push_int(struct stackint *stk, int val){
    if (stk->top == stk->size-1){
        stk->arr = resize_int_array(stk->arr, stk->size);
        stk->size *= RESIZE_FACTOR;
    }
    stk->arr[++stk->top] = val;
}

struct stackint *pop_int(struct stackint *stk){
    if (stk->top == -1){
        return NULL;
    }
    --stk->top;
}

void print_stackint(struct stackint *stk){
    if (stk->top == -1){
        printf("\nEmpty stack.\n");
        return;
    }
    printf("\nstack:\n-->");
    for (unsigned int i=0; i<=stk->top; ++i){
        printf(" %i", stk->arr[i]);
    }
    printf("\n");
}

void print_stackint_state(struct stackint *stk){
    printf("\nstack state:\n--> size = %i\n--> top = %i\n", 
        stk->size, stk->top);
}

#define STACK_SIZE 10
void test_stackint(){
    struct stackint stk;
    init_stackint(&stk);

    print_stackint(&stk);
    print_stackint_state(&stk);

    push_int(&stk, 17);
    push_int(&stk, 3);
    push_int(&stk, 2002);
    push_int(&stk, 1902);
    pop_int(&stk);

    print_stackint(&stk);
    print_stackint_state(&stk);

    for (int i=0; i<20; ++i){
        push_int(&stk, get_rand_int(1, 99));
    }

    print_stackint(&stk);
    print_stackint_state(&stk);

    for (int i=0; i<20; ++i){
        pop_int(&stk);
    }

    print_stackint(&stk);
    print_stackint_state(&stk);

    reset_stackint(&stk);
    print_stackint(&stk);
    print_stackint_state(&stk);
    pop_int(&stk);
    push_int(&stk, 1);

    print_stackint(&stk);
    print_stackint_state(&stk);

    free_stackint(&stk);
}