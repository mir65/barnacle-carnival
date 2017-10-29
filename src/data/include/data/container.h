#ifndef DATA_CONTAINER_H
#define DATA_CONTAINER_H

/* Common container attributes
 *
 * Assumption: Array is modified through this interface only.
 */

struct data_container {
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
};

#endif
