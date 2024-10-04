#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long unsigned int seed;
int set = 1;

void set_seed(long unsigned int sd){
    seed = sd;
    printf("new seed = %lu\n", seed);
    srand(seed);
    set = 0;
}

int get_rand_int(int min, int max)
{
    if (set == 1){
        seed = time(NULL);
        printf("seed = %lu\n", seed);
        srand(seed);
        set = 0;
    }
    return ((min) + (rand() % ((max) - (min) + 1)));
}