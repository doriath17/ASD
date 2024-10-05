#include <stdlib.h>
#include <limits.h>
#include <iso646.h>
#include "bst.h"
#include "util.h"


/**
 * Idea
 * The main idea of this algorithm is to pass each call information 
 * abount the min or max value a node could have. So min and max 
 * essentially represents the range a node's vale can be in.
 *      - When descending left it is important to keep info about the 
 *        max to set an upperbound. This is because node on the left 
 *        should be <= than the actual node's value.
 *      - When descending right it is important to keep info about the 
 *        max and the min: node's value must be smaller than the the last max
 *        (and the last max is set on the last right descend) but can be greater 
 *        than the actual node's value.
 * Every call actually controls that the total order proprerty is respected.
 * 
 * Time complexity:     Θ(n)
 * Space complexity:    Θ(1) 
 * 
 * Note:
 *      - the root will never cause violation.
 *      - an empty tree is always a BST by definition.
 *      - using t->key-1 or t->key+1 assure the unicity of the values.
 *        To allow different node to have the same value just use t->key.
 */
static int checkBST_impl(struct binary_tree *t, int min, int max){
    if (t != NULL){
        if (min <= t->key && max >= t->key){                // if the node is valid
            int sx = checkBST_impl(t->sx, min, t->key-1);   // assure its childs are valid
            int dx = checkBST_impl(t->dx, t->key+1, max);
            return sx && dx;
        }
        else {      
            return 0;                                       // the node is invalid
        }
    }
    else {                                                  // an empty tree is a BST
        return 1;
    }
}


// interface
int checkBST(struct binary_tree *t){
    return checkBST_impl(t, INT_MIN, INT_MAX);
}


/**
 * Idea
 * In a BST:
 *      - min is in the right-most node of the t->sx
 *      - max is in the left-most node of t->dx
 * This is because of the total order proprerty. So for ex.for the min: 
 *  - from the root continuing descending left.
 * 
 * Time complexity:     Θ(h) where h is the tree's height.
 * Space complexity:    Θ(1)
 * 
 * Note:
 *  - the search of min and max is a specialization of find / search.
 */
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


struct binary_tree *insertBST(struct binary_tree *t, int k){
    if (t not_eq NULL){
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