#include "bst.h"
#include <stdlib.h>
#include "util.h"

struct binary_tree *insertBST(struct binary_tree *t, int k){
    if (t != NULL){
        if (t->key == k){
            return t;
        }
        else if (t->key < k) {
            t->dx = insertBST(t->dx, k);
            return t;
        }
        else {
            t->sx = insertBST(t->sx, k);
            return t;
        }
    }
    else {
        return create_node(k);
    }
}

struct binary_tree *minBST(struct binary_tree *t){
    if (t!=NULL){
        if (t->sx != NULL){
            return minBST(t->sx);
        }
        else {
            return t;
        }
    }
    else {
        return t;
    }
}

struct binary_tree *maxBST(struct binary_tree *t){
    if (t!=NULL){
        if (t->dx != NULL){
            return maxBST(t->dx);
        }
        else {
            return t;
        }
    }
    else {
        return t;
    }
}


int checkBST(struct binary_tree *t, int min, int max){
    if (t != NULL){
        if (min <= t->key && max >= t->key){
            int sx = checkBST(t->sx, min, t->key-1);
            int dx = checkBST(t->dx, t->key+1, max);
            return sx && dx;
        }
        else {
            return 0;
        }
    }
    else {
        return 1;
    }
}

struct binary_tree *successorBST(struct binary_tree *t, int k){
    struct binary_tree *succ = NULL;
    if (t != NULL){
        if (t->key == k) {
            if (t->dx != NULL){
                succ = minBST(t->dx);
            }
        } else if (t->key < k){
            succ = successorBST(t->dx, k);
        } else {
            succ = successorBST(t->sx, k);
            if (succ == NULL){
                succ = t;
            }
        }
    }
    return succ;
}