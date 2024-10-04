#include "sorting.h"
#include "util.h"

#define LEFT(i)         ((i)*2 + 1)
#define RIGHT(i)        ((i)*2 + 2)

/**
 * heapsize :   the number of elements of the heap
 * i        :   the node where an almost-heap is rooted.
 * 
 * It compares the value in the node i with its left and right child.
 * Returns the max of these three values.
 */
static int find_max_node(int *arr, int heapsize, int i){
    int max = i, left = LEFT(i), right = RIGHT(i);
    if (left < heapsize && arr[max] < arr[left]){
        max = left;
    }
    if (right < heapsize && arr[max] < arr[right]){
        max = right;
    }
    return max;
}

void heapify(int *arr, int heapsize, int i){
    int max = find_max_node(arr, heapsize, i);
    if (max != i){
        int tmp = arr[i];
        arr[i] = arr[max];
        arr[max] = tmp;
        heapify(arr, heapsize, max);
    }
}

void build_heap(int *arr, int heapsize){
    for (int i=((heapsize-1)/2); i>-1; --i){
        heapify(arr, heapsize, i);
    }
}

int check_heap(int *arr, int heapsize, int i){
    if (i < heapsize){  // node i exists.
        if (find_max_node(arr, heapsize, i) == i){
            return check_heap(arr, heapsize, LEFT(i)) && check_heap(arr, heapsize, RIGHT(i));
        }
        else {
            return 0;
        }
    }
    return 1;
}

int check_heap_iter(int *arr, int heapsize, int i){
    int ci=i, li=0, lret=0;
    struct stackint sti, str;
    init_stackint(&sti);
    init_stackint(&str);

    while (ci >= 0 || !is_stackint_empty(&sti)){
        if (ci >= 0){
            if (ci < heapsize){
                if (find_max_node(arr, heapsize, ci) == ci){
                    push_int(&sti, ci);
                    ci = LEFT(ci);
                }
                else {
                    lret = 0;
                    li = ci;
                    ci = -1;
                }
            }
            else{
                lret = 1;
                li = ci;
                ci = -1;
            }
        }
        else{
            ci = top_int(&sti);
            if (li == LEFT(ci)){
                push_int(&str, lret);
                ci = RIGHT(ci);
            }
            else{
                lret = top_int(&str) && lret ? 1 : 0;
                li = ci;
                pop_int(&str);
                pop_int(&sti);
                ci = -1;
            }
        }
    }

    free_stackint(&sti);
    free_stackint(&str);

    return lret;
}

// 6 68 36 76 75 49 44 95 8 77

void heapsort(int *arr, int size){
    build_heap(arr, size);
    for (int i=size-1, tmp=0; i>=1; --i){
        tmp = arr[i];
        arr[i] = arr[0];
        arr[0] = tmp;
        --size;
        heapify(arr, size, 0);
    }
}