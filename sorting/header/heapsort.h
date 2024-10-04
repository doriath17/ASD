#ifndef HEAPSORT_H
#define HEAPSORT_H

/**
 * heapsize :   the number of elements of the heap
 * i        :   the node where an almost-heap is rooted.
 * 
 * It adjusts the heap rooted in i recursively so to maintain the
 * partial order condition on the complete binary tree.
 */
void heapify(int *arr, int heapsize, int i);

/**
 * heapsize :   the number of elements of the heap
 * i        :   the node where an almost-heap is rooted.
 * 
 * Given an array it will code an heap tree into it by using
 * heapify. 
 * The idea is that the array code a complete binary tree (CBT) and 
 * its leeves are heaps (beign them >= than their child since they don't 
 * exists). So internal nodes, the leeves parents are "almost-heap" and you
 * can use hepify on them to eventually adjust them and make them valid heaps.
 * Since the leeves are the half of the nodes of a binary tree, 
 * internal nodes indeces are in the interval: [0, (heapsize-1)/2].  
 */
void build_heap(int *arr, int heapsize);

/**
 * heapsize :   the number of elements of the heap
 * i        :   the node where an almost-heap is rooted.
 * 
 * By using a preorder checks if the array represents 
 * a valid heap.
 */
int check_heap(int *arr, int heapsize, int i);


/**
 * heapsize :   the number of elements of the heap
 * i        :   the node where an almost-heap is rooted.
 * 
 * By using a preorder checks if the array represents 
 * a valid heap.
 */
int check_heap_iter(int *arr, int heapsize, int i);

/**
 * size     : the number of elements.
 * 
 * This sorting algorithm see an array as a complete binary tree.
 * It builds an heap from this tree, then, iteratively , it finds
 * the max of the array (the tree's root node) and restore the 
 * heap using heapify.
 */
void heapsort(int *arr, int size);

#endif //  HEAPSORT_H