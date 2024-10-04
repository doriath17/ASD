#ifndef ARRAY_UTIL_H
#define ARRAY_UTIL_H

#define RESIZE_FACTOR   2u

/**
 * size : the number of elemets to initialize
 *  
 * populate the array with random values using the function
 * get_rand_int in "random.h". 
 * It assumes that size is valid. 
 */
void fill_rand_int(int *arr, unsigned int size, int min, int max);


/**
 * size : the number of elements of the array
 * 
 * It allocates an array of pointers on the heap using malloc.
 * Pointers are stored as void, to use the elements you need to 
 * cast them to the appropriate type
 * Returns NULL if there are errors in the allocation.
 */
void **get_void_ptr_array(unsigned int size);


/**
 * size : the number of elements of the array
 * 
 * It allocates an array of int on the heap using malloc.
 * Returns NULL if there are errors in the allocation.
 */
int *get_int_array(unsigned int size);


/**
 * size : the number of elements of the array
 * 
 * It allocates an array using get_array and initialize the
 * elements using fill_rand. 
 * Returns NULL if there are errors in the allocation.
 */
int *get_rand_int_array(unsigned int size, int min, int max);


/**
 * arr  : an array allocated with malloc
 * size : the number of elements of the array
 * 
 * These functions allocate a new array of size = size*2, 
 * copies arr into the new array and deallocates arr.
 * Both of them return a pointer to the new array or NULL
 * if there are allocations error.
 */
int *resize_int_array(int *arr, unsigned int size);
void **resize_void_ptr_array(void **arr, unsigned int size);

void print_int_array(int *arr, unsigned int size);

int check_order(int *A, unsigned int size);


#endif // ARRAY_UTIL_H