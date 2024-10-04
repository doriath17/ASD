#include "trees.h"
#include "util.h" 

struct binary_tree *insertBSTiter(struct binary_tree *t, int k){
    struct binary_tree *ct = t, *ret = NULL;
    struct stackptr stt;
    init_stackptr(&stt);

    while (ct != NULL || !is_stackptr_empty(&stt)){
        if (ct != NULL){
            if (ct->key == k){
                ret = ct;
                ct = NULL;
            } else if (ct->key < k) {
                push_ptr(&stt, (void *) ct);
                ct = ct->dx;
            } else {
                push_ptr(&stt, (void *) ct);
                ct = ct->sx;
            }
        } else if (ret != NULL){
            ct = (struct binary_tree *) top_ptr(&stt);
            if (ct->key < k){
                ct->dx = ret;
            } else {
                ct->sx = ret;
            }
            ret = ct;
            ct = NULL;
            pop_ptr(&stt);
        } else {
            ret = create_node(k);
        }
    }
    if (ret == NULL){
        ret = create_node(k);
    }
    free_stackptr(&stt);
    return ret;
}

int checkBSTiter(struct binary_tree *t, int min, int max){
    struct binary_tree *ct = t;  
    int cmin = min, cmax = max, csx = 0, cdx = 0, ret = -1, lmax = max;
    struct stackptr stt;
    init_stackptr(&stt);
    struct stackint stsx, stmax;
    init_stackint(&stsx);
    init_stackint(&stmax);

    while (ct != NULL || !is_stackptr_empty(&stt)){
        if (ct != NULL){
            if (cmin <= ct->key && cmax >= ct->key){
                push_ptr(&stt, (void *) ct);
                push_int(&stmax, cmax);
                cmax = ct->key-1;
                ct = ct->sx;   
            } else {
                ret = 0;
                ct = NULL;
            }
        } else if (ret != -1){
            ct = (struct binary_tree *) top_ptr(&stt);
            cmax = top_int(&stsx);
            if (lmax == cmax){
                csx = ret;
                push_int(&stsx, csx);
                cmin = ct->key+1;
                ct = ct->dx;
            } else {
                csx = top_int(&stsx);
                cdx = ret;
                ret = csx && cdx;
                pop_ptr(&stt);
                pop_int(&stsx);
                pop_int(&stmax);
                ct = NULL;
            }
        } else {
            ret = 1;
        }
    }
    if (ret == -1){
        ret = 1;
    }
    free_stackptr(&stt);
    free_stackint(&stsx);
    free_stackint(&stmax);
    return ret;
}

struct binary_tree *successorBSTiter(struct binary_tree *t, int k){
    struct binary_tree *ct = t, *ret = NULL, *lt = NULL;
    struct stackptr stt;
    init_stackptr(&stt);

    while (ct != NULL || !is_stackptr_empty(&stt)){
        if (ct != NULL){
            if (ct->key == k){
                if (ct->dx != NULL){
                    ret = minBST(ct->dx);
                    ct = NULL;
                } 
            } else if (ct->key < k){
                lt = ct;
                ct = ct->dx;
            } else {
                lt = ct;
                push_ptr(&stt, (void *) ct);
                ct = ct->sx;
            }
        } else {
            ct = (struct binary_tree *) top_ptr(&stt);
            if (lt != ct->dx && ret == NULL){
                ret = ct;
            }
            lt = ct;
            ct = NULL;
            pop_ptr(&stt);
        }
    }
    free_stackptr(&stt);
    return ret;
}