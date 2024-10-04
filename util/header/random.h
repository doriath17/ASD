#ifndef RANDOM_H
#define RANDOM_H

/**
 * The seed for the random generator is set automatically
 * the first time you make a call to get_rand_int.
 * However you can set the seed manually using set seed.
 */
extern long unsigned int seed;
void set_seed(long unsigned int seed);

int get_rand_int(int min, int max);

#endif // RANDOM_H
