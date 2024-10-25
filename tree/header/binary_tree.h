#ifndef BINARY_TREE_H
#define BINARY_TREE_H

struct binary_tree {
    int key;
    struct binary_tree *sx;
    struct binary_tree *dx;
};

struct binary_tree * create_node(int key);
void free_binary_tree(struct binary_tree *t);

struct binary_tree *insert(struct binary_tree *t, int k);

void preorder(struct binary_tree *t);
void inorder(struct binary_tree *t);
void inorder_inverse(struct binary_tree *t);
void postorder(struct binary_tree *t);
void breadth(struct binary_tree *t);
void breadth_lvs(struct binary_tree *t);

#endif // BINARY_TREE_H