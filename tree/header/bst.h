#ifndef BST_H
#define BST_H

#include "binary_tree.h"

int checkBST(struct binary_tree *t, int min, int max);
int checkBSTiter(struct binary_tree *t, int min, int max);

struct binary_tree *insertBST(struct binary_tree *t, int k);
struct binary_tree *insertBSTiter(struct binary_tree *t, int k);

struct binary_tree *minBST(struct binary_tree *t);
struct binary_tree *maxBST(struct binary_tree *t);

struct binary_tree *successorBST(struct binary_tree *t, int k);
struct binary_tree *successorBSTiter(struct binary_tree *t, int k);

#endif // BST_H