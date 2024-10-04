#include <stdio.h>
#include <stdlib.h>
#include "util.h"
#include "sorting.h"
#include "testing.h"

void test_example(){
    int arr[TEST_EX_SIZE];     
    printf("Example test.\ninput:\n");

    fill_rand_int(arr, TEST_EX_SIZE, TEST_MIN_VAL_EX, TEST_MAX_VAL_EX);
    print_int_array(arr, TEST_EX_SIZE);

    printf("\nheap:\n");
    build_heap(arr, TEST_EX_SIZE);
    print_int_array(arr, TEST_EX_SIZE);

    printf("--> build_heap resutl (recu): %s\n", 
        check_heap(arr, TEST_EX_SIZE, 0) ? "true" : "false");
    printf("--> build_heap result (iter): %s\n", 
        check_heap_iter(arr, TEST_EX_SIZE, 0) ? "true" : "false");

    heapsort(arr, TEST_EX_SIZE);
    printf("\noutput:\n");
    print_int_array(arr, TEST_EX_SIZE);
    printf("\n");
}

void test_build(int *arr, int lenght, int *count_check_heap, int *count_check_heap_iter){
    build_heap(arr, lenght);
    if (check_heap(arr, lenght, 0) == 1){
        ++(*count_check_heap);
    }
    if (check_heap_iter(arr, lenght, 0) == 1){
        ++(*count_check_heap_iter);
    }
}

void test_hs(int *arr, int lenght, int *count){
    heapsort(arr, lenght);
    if (check_order(arr, lenght) == 1){
        ++(*count);
    }
}


void test(){
    int arr[TEST_MAX_SIZE];
    int lenght = 0, count_check_heap=0, count_check_heap_iter=0, count=0;

    printf("Testing...\n");

    for (int i=0; i<TEST_NUM; ++i){
        lenght = get_rand_int(0, TEST_MAX_SIZE);
        fill_rand_int(arr, lenght, TEST_MIN_VAL, TEST_MAX_VAL); // overwrite arr
        test_build(arr, lenght, &count_check_heap, &count_check_heap_iter);
        test_hs(arr, lenght, &count);   
    }
    printf("\nResults\n--> heapsort -> %i / %i\n--> build    -> recu: %i, iter: %i\n", 
        count, TEST_NUM, count_check_heap, count_check_heap_iter);
}

void test_heapsort(){
    printf("\n\nTESTING: heapsort\n\n");
    test_example();
    test();
    printf("\nTESTING: finished.\n");
}