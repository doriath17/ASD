#include "testing.h"
#include "util.h"
#include <stdio.h>

void test_sort_example(void (*sort)(int *, int)){
    int arr[TEST_EX_SIZE];     
    printf("Example test.\ninput:\n");

    fill_rand_int(arr, TEST_EX_SIZE, TEST_MIN_VAL_EX, TEST_MAX_VAL_EX);
    print_int_array(arr, TEST_EX_SIZE);

    sort(arr, TEST_EX_SIZE);
    printf("\noutput:\n");
    print_int_array(arr, TEST_EX_SIZE);
    printf("\n");
}

void test_sort(void (*sort)(int *, int)){
    int arr[TEST_MAX_SIZE], lenght=0, count=0;

    printf("Testing...\n");

    for (int i=0; i<TEST_NUM; ++i){
        lenght = get_rand_int(0, TEST_MAX_SIZE);
        fill_rand_int(arr, lenght, TEST_MIN_VAL, TEST_MAX_VAL); // overwrite arr
        sort(arr, lenght);
        if (check_order(arr, lenght)){
            ++count;
        }
    }

    printf("\nResults\n--> sort -> %i / %i\n", 
    count, TEST_NUM);
}

void full_test(void (*sort)(int *, int)){
    printf("\n\nTESTING: heapsort\n\n");
    test_sort_example(sort);
    test_sort(sort);
    printf("\nTESTING: finished.\n");
}