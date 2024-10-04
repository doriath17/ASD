#include <stdlib.h>
#include <stdio.h>
#include "random.h"
#include "array_util.h"

void fill_rand_int(int *arr, unsigned int size, int min, int max){
    for (unsigned int i=0; i<size; ++i){
        arr[i] = get_rand_int(min, max);
    }
}

int *get_int_array(unsigned int size){
    int *arr = (int *) malloc(sizeof(int) * size);
    if (arr == NULL){
        printf("Error: allocation fail in get_int_array.\n");
        return NULL;
    }
    return arr;
}

void **get_void_ptr_array(unsigned int size){
    void **arr = (void **) malloc(sizeof(void *) * size);
    if (arr == NULL){
        printf("Error: allocation fail in get_void_ptr_array.\n");
        return NULL;
    }
    return arr;
}

int *get_rand_int_array(unsigned int size, int min, int max){
    int *arr = get_int_array(size);
    if (arr == NULL){
        return NULL;
    }
    else {
        fill_rand_int(arr, size, min, max);
        return arr;
    }
}

int *resize_int_array(int *arr, unsigned int size){
    int *new_arr = get_int_array(size*RESIZE_FACTOR);
    if (new_arr == NULL){
        return NULL;
    }
    for (unsigned int i=0; i<size; ++i){
        new_arr[i] = arr[i];
    }
    free(arr);
    return new_arr;
}

void **resize_void_ptr_array(void **arr, unsigned int size){
    void **new_arr = get_void_ptr_array(size*RESIZE_FACTOR);
    if (new_arr == NULL){    
        return NULL;
    }
    for (unsigned int i=0; i<size; ++i){
        new_arr[i] = arr[i];
    }
    free(arr);
    return new_arr;
}

void print_int_array(int *arr, unsigned int size){
    printf("--> ");
    for (unsigned int i=0; i<size; ++i){
        printf(" %i", arr[i]);
    }
    printf("\n");
}


int check_order(int *arr, unsigned int size)
{
    int ord = 1; // ascending order
    for (unsigned int i=1; i < size && ord; ++i)
        if (arr[i-1] > arr[i])
            ord = 0;
    return ord;
}