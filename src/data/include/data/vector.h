#ifndef DATA_VECTOR_H
#define DATA_VECTOR_H

#include <stdbool.h>
#include <stdlib.h>

/* Container with guaranteed contiguous storage
 *
 * Assumption: Array is modified through this interface only.
 */

struct data_vector {
    /* Array used for storage */

    void *array;

    /* Size of one element
     *
     * Example:
     *
     *   int array[10];
     *
     *   Size is sizeof(int).
     */

    size_t element_size;

    /* Length of array in terms of element_size.
     *
     * Example:
     *
     *   int array[10];
     *
     *   Capacity is 10*1, not 10*sizeof(int).
     */

    size_t capacity;

    /* Private */

    /* Number of elements stored */

    size_t size;
};

/* Initializes. */

void data_vector_init(struct data_vector*);

/* Returns the number of elements stored. */

size_t data_vector_size(struct data_vector*);

/* Returns true if size is zero. */

bool data_vector_empty(struct data_vector*);

/* Returns true if size is at capacity. */

bool data_vector_full(struct data_vector*);

/* Returns the address of the element at the front.
 *
 * If empty, begin is the same as end.
 */

void *data_vector_begin(struct data_vector*);

/* Returns the address of the element after the element at the back.
 *
 * If empty, begin is the same as end.
 */

void *data_vector_end(struct data_vector*);

/* Adds an element to the back.
 *
 * Parameter element is a pointer to the element to be stored.
 *
 * If full, does nothing.
 */

void data_vector_push_back(struct data_vector*, void const *element);

/* Removes the element at the back.
 *
 * If empty, undefined behavior.
 */

void data_vector_pop_back(struct data_vector*);

/* Removes the element at the iterator.
 *
 * If empty, undefined behavior.
 *
 * Order of remaining elements is undefined.
 */

void data_vector_erase_at(struct data_vector*, void *iterator);

#endif
