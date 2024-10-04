#ifndef ASD_QUEUEINT_H
#define ASD_QUEUEINT_H

/**
 * arr      :   the array implementing the queue.
 * head     :   the beginning of the queue.
 * tail     :   the end of the queue.
 * size     :   the max number of elements the queue can hold.
 * 
 * The queue has a beginning (head) and an end (tail).
 * It implements a FIFO policy:
 *      when an element is insert, it is inserted on the tail
 *      (at the end of the queue).
 *      when an element is removed, it is removed from the head
 *      (from the beginning of the queue).
 * 
 * Implementation details.
 * To implement a queue of n-1 elements it is used an array of size = n 
 * elements. Position in the array follow a circular order: the position 
 * after size-1 is 0.
 * 
 * Emptiness: if head == tail == -1 the queue is empty.
 *      -> head and tail can be the same only if there is only one element.
 * Fullness:  if head = tail + 1 the queue is full
 *      -> to insert a resize should take palce.
 */
struct queueint {
    int *arr;
    int size;
    int head;
    int tail;
};




/*******************************************************************************
 * 
 *
 * 
 * Functions to modify the queue's state
 * 
 * 
 * 
 *******************************************************************************/




/**
 * qint     :   a not-NULL queueint variable (static o dinamic) to initialize.
 * 
 * This function initializes the queue to its initial state:
 *      -   an array of DEFAULT_QUEUE_SIZE elements is malloc-allocated.
 *      -   size is then set to DEFAULT_QUEUE_SIZE
 *      -   head = -1   // emptiness
 *      -   tail = -1
 * 
 * It returns a pointer to the new allocated queueint structure.
 * It returns NULL if there is a problem with malloc: the caller should
 * control the return value to assure no errors have occurred.
 * 
 * ATTENTION: do not use this function on a already initialized queueint:
 * this function will not free the previous array. If it has been allocated
 * using malloc, then a memory leakage could occur. Use reset_queueint instead.
 */
#define DEFAULT_QUEUE_SIZE  10
struct queueint *init_queueint(struct queueint *quint);


/**
 * qint     :   a not-NULL queueint variable (static o dinamic) to initialize.
 * 
 * You can use this function if you want to re-initialize a queueint to 
 * its default state. It will free and replace the already initialized array.
 *
 * Return
 * It returns a pointer to the new allocated queueint structure.
 * It returns NULL if there is a problem with malloc: the caller should
 * control the return value to assure no errors have occurred. 
 */
#define QUEUE_RESIZE_FACTOR 2
struct queueint *reset_queueint(struct queueint *quint);


/**
 * qint     :   a not-NULL queueint variable (static o dinamic) to initialize.
 * 
 * Return
 * This function frees the queue's malloc-allocated array. It is intended 
 * to be used just before a queueint goes out of scope to avoid memory leakage. 
 */
void free_queueint(struct queueint *quint);


/**
 * qint     :   a not-NULL queueint variable (static o dinamic) to initialize.
 * k        :   value to insert.
 * 
 * This function will insert the value k on the tail and update tail.
 * If the queue is full a resize can take place in order to allow
 * the expansion.
 * 
 * Return
 * It returns quint but can return NULL if there were problems with the resize:
 * in such a case the quint is not modified and can be reused.
 */
struct queueint *enqueue_int(struct queueint *quint, int k);

/**
 * qint     :   a not-NULL queueint variable (static o dinamic) to initialize.
 * 
 * This function will remove the value on the head and update head.
 * If the queue is empty calling this function will do nothing.
 * If there is only one element in the queue, head and tail are set to 
 * their default values (-1).
 * 
 * Return
 * It returns quint or NULL if the queue was empty.
 */
struct queueint *dequeue_int(struct queueint *quint);




/*******************************************************************************
 * 
 * 
 * 
 * Functions to retrieve information from the queue.
 * This function will not modify the queue's state.
 * 
 * 
 * 
 *******************************************************************************/




/**
 * qint     :   a not-NULL queueint variable (static o dinamic) to initialize.
 * 
 * This functions verifies if quint is empty.
 * 
 * Return
 * If the queue is empty:       return = 1
 * If the queue is not empty:   return = 0
 */
int is_queueint_empty(const struct queueint *quint);


/**
 * qint     :   a not-NULL queueint variable (static o dinamic) to initialize.
 * 
 * This functions verifies if quint is full.
 * 
 * Return
 * If the queue is full:       return = 1
 * If the queue is not full:   return = 0
 */
int is_queueint_full(const struct queueint *quint);


/**
 * qint     :   a not-NULL queueint variable (static o dinamic) to initialize.
 * 
 * This function returns the value in tail and should be used 
 * only after assuring the queue is not empty.
 * 
 * Return
 * the value on tail.
 */
int tail_int(struct queueint *quint);


/**
 * qint     :   a not-NULL queueint variable (static o dinamic) to initialize.
 * 
 * This function returns the value in head and should be used 
 * only after assuring the queue is not empty.
 * 
 * Return
 * the value on head.
 */
int head_int(struct queueint *quint);

void print_queueint_state(struct queueint *quint);
void print_queueint(struct queueint *quint);
void print_queueint_repr(struct queueint *quint);

#endif // ASD_QUEUEPTR_H