#ifndef TIMER_H
#define TIMER_H

#include <time.h>


clock_t get_exec_time(void (*func)(void *param), void *param);

void print_exec_time(void (*func)(void *param), void *param);

#endif // TIMER_H