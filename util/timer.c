#include "time.h"
#include <stdio.h>

clock_t get_exec_time(void (*func)(void *param), void *param){
    clock_t start = clock();
    func(param);
    clock_t end = clock();
    return (end - start) / CLOCKS_PER_SEC;
}

void print_exec_time(void (*func)(void *param), void *param){
    printf("clock per sec: %lu\n", CLOCKS_PER_SEC);
    printf("Execution time: %.9ld\n", get_exec_time(func, param));
}