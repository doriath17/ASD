#include "util.h"
#include "sorting.h"

void merge(int *A, int p, int q, int r)
{
    int left_len = q-p+1, right_len = r-q;
    int left[q-p+1], right[r-q];
    for (unsigned int i=0; i<left_len; ++i)
        left[i] = A[p+i];
    for (unsigned int i=0; i<right_len; ++i)
        right[i] = A[q+1+i];

    unsigned int i=0, j=0, k=p;

    while (i < left_len && j < right_len){
        if (left[i] <= right[j])
            A[k++] = left[i++];
        else A[k++] = right[j++];
    }
    if (i == left_len)
        while (j < right_len)
            A[k++] = right[j++];
    else 
        while (i < left_len)
            A[k++] = left[i++];
}

void merge_sort(int *A, int p, int r)
{
    if (p < r) {
        int q = (p+r)/2;
        merge_sort(A, p, q);
        merge_sort(A, q+1, r);
        merge(A, p, q, r);
    }
}

void merge_sort_iter(int *arr, int p, int r){
    int cp = p, cr = r, cq = 0, lr = 0; // lr = call return info: last call's cr
    struct stackint stp, str, stq;
    init_stackint(&stp);
    init_stackint(&str);
    init_stackint(&stq);

    while (cp <= cr || stq.top > -1){
        if (cp <= cr){              // simualte first call
            if (cp < cr){           // recursive case
                cq = (cp + cr) / 2;
                push_int(&str, cr);
                push_int(&stq, cq);
                cr = cq;
            }
            else {                  // base case (cp == cr)
                lr = cr;
                cr = cp - 1;        // end of call condition
            }
        }
        else {
            cr = top_int(&str);         // restore parent's contex after the first call
            cq = top_int(&stq);
            if (lr != cr){          // simulate second call
                push_int(&stp, cp);
                cp = cq + 1;
            }
            else {
                cp = top_int(&stp);     // restore parent's contex after the second call
                merge(arr, cp, cq, cr);
                lr = cr;            // simulate termination
                cr = cp - 1;
                pop_int(&stp);
                pop_int(&str);
                pop_int(&stq);
            }
        }
    }

    free_stackint(&stp);
    free_stackint(&str);
    free_stackint(&stq);
}

void test_merge(){
    int size = 1000000, min = 1, max = 99;
    int arr[size];

    fill_rand_int(arr, size, min, max);
    // print_int_array(arr, size);

    merge_sort(arr, 0, size-1);
    // print_int_array(arr, size);
    printf("order: %i\n", check_order(arr, size));

    fill_rand_int(arr, size, min, max);
    // print_int_array(arr, size);
    merge_sort_iter(arr, 0, size-1);
    // print_int_array(arr, size);
    printf("order: %i\n", check_order(arr, size));
}