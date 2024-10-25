#ifndef BST_H
#define BST_H

#include "binary_tree.h"

/**
 * t        :   a binary tree (can be NULL)
 * 
 * This function checks if the binary tree t is a 
 * binary search tree or not.
 * 
 * returns
 * 1 if the tree is a BST.
 * 0 otherwise (even if t == NULL).
 */
int checkBST(struct binary_tree *t);
int checkBSTiter(struct binary_tree *t);

/**
 * t        :   a binary tree (can be NULL)
 * k        :   value to insert
 * 
 * This function will insert the value k in t maintaining 
 * the total order.
 * 
 * returns
 * the modified tree: t can change.
 * NULL if there is an allocation error.
 */
struct binary_tree *insertBST(struct binary_tree *t, int k);
struct binary_tree *insertBSTiter(struct binary_tree *t, int k);


/**
 * t        :   a binary tree (can be NULL)
 * k        :   value to search for
 * 
 * This function will search the value k in t.
 * 
 * returns
 * a node containing k.
 * NULL if k is not in t.
 */
struct binary_tree *searchBST(struct binary_tree *bst, int k);


/**
 * t        :   a binary tree (can be NULL)
 * 
 * This function returns the minimum value of t.
 * 
 * returns
 * the node containing the min: 
 *  - left-most node of t->sx or t itself if t->sx == NULL 
 *  - NULL if t == NULL
 */
struct binary_tree *minBST(struct binary_tree *t);

/**
 * t        :   a binary tree (can be NULL)
 * 
 * This function returns the maximum value of t.
 * 
 * returns
 * the node containing the max: 
 *  - right-most node of t->dx or t itself if t->dx == NULL 
 *  - NULL if t == NULL
 */
struct binary_tree *maxBST(struct binary_tree *t);

struct binary_tree *successorBST(struct binary_tree *t, int k);
struct binary_tree *successorBSTiter(struct binary_tree *t, int k);

struct binary_tree *predecessorBST(struct binary_tree *t, int k);

#endif // BST_H