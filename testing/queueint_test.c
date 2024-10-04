#include <stdio.h>
#include "util.h"
#include "queueint.h"
#include "testing.h"

void queueint_test(){
    struct queueint quint;
    init_queueint(&quint);
    // print_queueint_state(&quint);

    // for (unsigned int i=0; i<10; ++i){
    //     enqueue_int(&quint, get_rand_int(1, 99));
    // }

    // print_queueint_state(&quint);
    // print_queueint(&quint);
    // print_queueint_repr(&quint);

    // for (unsigned int i=0; i<10; ++i){
    //     dequeue_int(&quint);
    // }

    printf("\n\nTesting linearize_arr.\n");
    for (unsigned int i=0; i<10; ++i){
        enqueue_int(&quint, get_rand_int(1, 99));
    }
    for (unsigned int i=0; i<5; ++i){
        dequeue_int(&quint);
    }

    printf("\nFirst loop\n");
    print_queueint_state(&quint);
    print_queueint(&quint);
    print_queueint_repr(&quint);

    for (unsigned int i=0; i<10; ++i){
        enqueue_int(&quint, get_rand_int(1, 99));
    }

    printf("\nSecond loop\n");
    enqueue_int(&quint, get_rand_int(1, 99));
    enqueue_int(&quint, get_rand_int(1, 99));
    enqueue_int(&quint, get_rand_int(1, 99));
    enqueue_int(&quint, get_rand_int(1, 99));
    enqueue_int(&quint, get_rand_int(1, 99));
    enqueue_int(&quint, get_rand_int(1, 99));

    print_queueint_state(&quint);
    print_queueint(&quint);
    print_queueint_repr(&quint);

    free_queueint(&quint);
}