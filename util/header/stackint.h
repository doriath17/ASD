#ifndef STACKINT_H
#define STACKINT_H

#define DEFAULT_STK_SIZE 10u

/**
 * arr  :    an array allocated with malloc.
 * size :    number of elements of arr.
 * top  :    an index to the top of the stack 
 * 
 * Default state
 * arr  :    a malloc allocated array of DEFAULT_STK_SIZE elements.
 * size :    DEFAULT_STK_SIZE
 * top  :    -1
 * 
 * To set a stackint variable to its default state use init_stackint()
 * See definition for details.
 */
struct stackint {
    int *arr;
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
struct stackint *init_stackint(struct stackint *stk);

/**
 * Use this function if you have a stack already initialized 
 * and want to reuse it. It frees the array and then call init_stackint.
 * Return stk if success or NULL for failure. 
 */
struct stackint *reset_stackint(struct stackint *stk);

/**
 * free the array associated with the stk.
 */
void free_stackint(struct stackint *stk);


/**
 * If the stack is empty:       return = 1
 * If the stack is not empty:   return = 0
 */
int is_stackint_empty(const struct stackint *stk);

/**
 * If the stack is not empty then it will return the 
 * value on the stack's top.
 * Else, if the stack is indeed empty, it will return -1.
 */
int top_int(const struct stackint *stk);

/**
 * push and pop are the only functions beside the init_stackint
 * which can change the stack's state. 
 * 
 * push will write val on arr[top + 1].
 * pop will move top to top - 1.
 * 
 * return values are the stack in its new state or NULL 
 * meaning that the function failed:
 *      -   push can fail when there is an allocation problem.
 *      -   pop can fail when the stack is empty.
 * So push failure is the syntom of a more serious problem.
 */
struct stackint *push_int(struct stackint *stk, int val);
struct stackint *pop_int(struct stackint *stk);

void print_stackint(struct stackint *stk);

void print_stackint_state(struct stackint *stk);

void test_stackint();

#endif // STACKINT_H
