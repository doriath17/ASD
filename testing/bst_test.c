#include "trees.h"
#include "testing.h"
#include <stdio.h>
#include "util.h"

void test_checkBST(){

}

void bst_test(){
    struct binary_tree *bst = NULL;
    // int k = 47;
    
    set_seed(1728228991);
    int k = get_rand_int(TEST_MIN_VAL_EX, TEST_MAX_VAL_EX);

    printf("creating bst: n = %i\n", TEST_EX_SIZE);
    for (int i=0; i<TEST_EX_SIZE; ++i){
        bst = insertBST(bst, get_rand_int(TEST_MIN_VAL_EX, TEST_MAX_VAL_EX));
    }
    printf("\ninorder:\n");
    inorder(bst);
    printf("\n\ncheck: %s\n", checkBST(bst)?"true":"false");

    printf("search for k = %i      -> %s\n", k, searchBST(bst, k)?"found":"not found");
    printf("search for successor   -> %i\n", successorBST(bst, k)->key);
    printf("search for predecessor -> %i\n", predecessorBST(bst, k)->key);


    free_binary_tree(bst);
}