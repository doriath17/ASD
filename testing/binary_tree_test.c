#include "trees.h"
#include "testing.h"
#include "util.h"
#include <stdio.h>

void binary_tree_test(){
    struct binary_tree *bt;

    set_seed(17);

    int arr[TEST_EX_SIZE];
    fill_rand_int(arr, TEST_EX_SIZE, TEST_MIN_VAL_EX, TEST_MAX_VAL_EX);
    print_int_array(arr, TEST_EX_SIZE);

    for (int i=0; i<TEST_EX_SIZE; ++i){
        bt = insertBST(bt, arr[i]);
    }

    printf("Testing tree views.\n\n");

    // preorder(bt);
    // printf("\n");

    // inorder(bt);
    // printf("\n");

    // postorder(bt);
    // printf("\n");

    // breadth(bt);
    // printf("\n");

    breadth_lvs(bt);
    printf("\n");
}