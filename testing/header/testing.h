#ifndef TESTING_H
#define TESTING_H

/**
 * TEST_SIZE :   It represents on how many arrays the test will be done. 
 * TEST_MIN_SIZE  :   It is the min size a testing array will have.
 * TEST_MAX_SIZE  :   It is the max size a testing array will have. 
 * TEST_MIN_VAL   :   It is min value of an array element
 * TEST_MIN_VAL   :   It is max value of an array element   
 */
#define TEST_NUM                1000
#define TEST_CASES              10
#define TEST_MIN_SIZE           0
#define TEST_MAX_SIZE           5000
#define TEST_MIN_VAL            1
#define TEST_MAX_VAL            TEST_MAX_SIZE
#define TEST_EX_SIZE            10
#define TEST_MIN_VAL_EX         0
#define TEST_MAX_VAL_EX         99

/**
 * 
 */
void test_heapsort();

void test_sort_example(void (*sort)(int *, int));

void test_sort(void (*sort)(int *, int));

void full_test(void (*sort)(int *, int));

void queueint_test();

void bst_test();

#endif  //  TESTING_H