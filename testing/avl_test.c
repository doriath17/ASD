#include <stdio.h>
#include "util.h"
#include "avl.h"
#include "testing.h"

void test(){
    struct avl_tree *avl;
    int count_avl = 0, count_abr = 0;

    for (int i=0, k=0; i<TEST_NUM; ++i){
        avl = NULL;
        k = get_rand_int(TEST_MIN_SIZE, TEST_MAX_SIZE);
        for (int j=0; j<k; ++j){
            avl = insertAVL(avl, get_rand_int(TEST_MIN_VAL_EX, TEST_MAX_VAL_EX));
        }
        if (checkAVL(avl)){
            ++count_avl;
        }
        if (checkBST_avl(avl)){
            ++count_abr;
        }
        free_avl_tree(avl);
    }
    printf("avl = %i\n", count_avl);
    printf("abr = %i\n", count_abr);
}

void avl_example(){
    struct avl_tree *avl;

    set_seed(1728297931);

    for (int i=0; i<TEST_EX_SIZE; ++i){
        avl = insertAVL(avl, get_rand_int(TEST_MIN_VAL_EX, TEST_MAX_VAL_EX));
    }

    printf("inorder:\n");
    inorder_avl(avl);
    printf("\nbreadth:\n");
    breadth_lvs_avl(avl);

    printf("check (ABR)= %s\n", checkBST_avl(avl) ? "true" : "false");
    printf("check (AVL)= %s\n", checkAVL(avl) ? "true" : "false");
}

void avl_test(){
    avl_example(); 
    test();
}