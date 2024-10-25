#include "util.h"
#include "trees.h"

#include "testing.h"

#include <stdio.h>
#include <limits.h>

int main(){
    struct binary_tree bt, *pbt = &bt;
    for (int i=0; i<10; ++i){
        pbt = insertBST(pbt, get_rand_int(1, 99));
    }
    inorder_inverse(pbt);
    return 0;       
}