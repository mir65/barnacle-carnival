#ifndef DATA_RING_H
#define DATA_RING_H

#include <stdbool.h>
#include <stdlib.h>
#include <data/container.h>

/* Container with front and back operations */

struct data_ring {
    /* Common container attributes
     *
     * .array must fit .capacity + 1 elements.
     */

    struct data_container container;

    /* Private */

    /* Length of .container.array in bytes */

    size_t array_length;

    /* Iterator after last byte of array */

    char *array_end;

    /* Iterator at front */

    char *begin;

    /* Iterator at element after end */

    char *end;

    /* Iterator at end */

    char *end_minus_one;
};

/* Initializes. */

void data_ring_init(struct data_ring*);

/* Returns the number of elements stored. */

size_t data_ring_size(struct data_ring*);

/* Returns true if size is zero. */

bool data_ring_empty(struct data_ring*);

/* Returns true if size is at capacity. */

bool data_ring_full(struct data_ring*);

/* Returns the address of the element at the front.
 *
 * If empty, begin is the same as end.
 */

void *data_ring_begin(struct data_ring*);

/* Returns the address of the element after the element at the back.
 *
 * If empty, begin is the same as end.
 */

void *data_ring_end(struct data_ring*);

/* Returns the address of the element at the back.
 *
 * If empty, end_minus_one is begin - 1.
 */

void *data_ring_end_minus_one(struct data_ring*);

/* Adds an element to the front.
 *
 * Parameter element is a pointer to the element to be stored.
 *
 * If full, undefined behavior.
 */

void data_ring_push_front(struct data_ring*, void const *element);

/* Removes the element at the front.
 *
 * If empty, undefined behavior.
 */

void data_ring_pop_front(struct data_ring*);

/* Adds an element to the back.
 *
 * Parameter element is a pointer to the element to be stored.
 *
 * If full, undefined behavior.
 */

void data_ring_push_back(struct data_ring*, void const *element);

/* Removes the element at the back.
 *
 * If empty, undefined behavior.
 */

void data_ring_pop_back(struct data_ring*);

#endif
