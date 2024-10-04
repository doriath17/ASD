#ifndef STACKPTR_H
#define STACKPTR_H

#define DEFAULT_STK_SIZE 10u

/**
 * arr  :    an array allocated with malloc, each element is 
 *           a pointer to void.
 * size :    number of elements of arr.
 * top  :    an index to the top of the stack 
 * 
 * Default state
 * arr  :    a malloc allocated array of DEFAULT_STK_SIZE elements.
 * size :    DEFAULT_STK_SIZE
 * top  :    -1
 * 
 * To set a stackint variable to its default state use init_stackptr()
 * See definition for details.
 */
struct stackptr {
    void **arr;
    int size;   
    int top;   
};

/**
 * stk :    a stackint structure (can be a local variable
 *          or a heap allocated one).
 * 
 * It initializes the stack to its default state.
 *      -   arr allocated with get_array ("array_util.h")
 *      -   size = DEFAULT_STK_SIZE
 *      -   top = -1
 * ATTENTION: it simply replace the arr field with a pointer 
 * returned by get_array: if arr points to an array allocated on the 
 * heap there could me memory leakage. You can use reset_stackint to 
 * avoid this situation.
 * Returns the pointer received as input or NULL if 
 * get_array() failed. 
 */
struct stackptr *init_stackptr(struct stackptr *stk);

/**
 * Use this function if you have a stack already initialized 
 * and want to reuse it. It frees the array and then call init_stackptr.
 * Return stk if success or NULL for failure. 
 */
struct stackptr *reset_stackptr(struct stackptr *stk);


/**
 * free the array associated with the stk.
 */
void free_stackptr(struct stackptr *stk);


/**
 * If the stack is empty:       return = 1
 * If the stack is not empty:   return = 0
 */
int is_stackptr_empty(const struct stackptr *stk);


/**
 * If the stack is not empty then it will return the 
 * value on the stack's top.
 * Else, if the stack is indeed empty, it will return -1.
 */
void *top_ptr(const struct stackptr *stk);


/**
 * push and pop are the only functions beside the init_stackint
 * which can change the stack's state. 
 * 
 * push will write val on arr[top + 1].
 * pop will move top to top - 1.
 * 
 * return values are the stack in its new state or NULL 
 * meaning that the function failed.
 */
struct stackptr *push_ptr(struct stackptr *stk, void *ptr);
struct stackptr *pop_ptr(struct stackptr *stk);


/**
 * Display stack informations.
 */
void print_stackptr_state(struct stackptr *stk);

void test_stackptr();

#endif // STACKPTR_H