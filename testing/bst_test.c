#include "trees.h"
#include "testing.h"
#include <stdio.h>
#include "util.h"

void test_checkBST(){
    struct binary_tree *bt;
    int size = 0, count = 0, iterc = 0, count_succ = 0;
    printf("Testing check\n");

    for (int i=0, min, max, k; i<TEST_NUM; ++i){
        bt = NULL;
        size = get_rand_int(TEST_MIN_SIZE, TEST_MAX_SIZE);
        for (int j=0; j<size; ++j){
            // bt = insertBST(bt, get_rand_int(TEST_MIN_VAL, TEST_MAX_VAL));
            bt = insertBSTiter(bt, get_rand_int(TEST_MIN_VAL, TEST_MAX_VAL));
        }

        if (bt == NULL){
            min = 0;
            max = 0;
        } else {
            min = minBST(bt)->key;
            max = maxBST(bt)->key;
        }

        if (checkBST(bt)){
            ++count;
        }
        if (checkBSTiter(bt)){
            ++iterc;
        }

        k = get_rand_int(TEST_MIN_VAL, TEST_MAX_VAL);
        successorBST(bt, k);

        free_binary_tree(bt);
    }

    printf("result: %i / %i / %i\n", count, iterc, TEST_NUM);
}

void bst_test(){
    int size = 10, min = 1, max = 99;
    struct binary_tree *bt;

    for (int i = 0; i<size; ++i){
        // bt = insertBST(bt, i);
        // bt = insertBST(bt, get_rand_int(min, max));
        // bt = insertBSTiter(bt, i);
        bt = insertBSTiter(bt, get_rand_int(min, max));
    }

    printf("bst:\n");
    breadth_lvs(bt);
    printf("element inorder:\n");
    inorder(bt);


    struct binary_tree *bt_min = minBST(bt), *bt_max = maxBST(bt);
    printf("\nmin = %i, max = %i, check: %s\n",
        bt_min->key, bt_max->key, checkBST(bt)? "true" : "false");

    int k = get_rand_int(min, max);
    printf("k = %i --> successor (recu): %i\n", k, successorBST(bt, k)->key);
    printf("k = %i --> successor (iter): %i\n", k, successorBSTiter(bt, k)->key);

    // test_checkBST();
}