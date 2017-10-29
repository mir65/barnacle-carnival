#include <string.h>
#include <data/ring.h>

/* Returns parameter iterator wrapped at the array end.
 *
 * Assumption: Paramater iterator is a valid iterator position + 1.
 */

static char *wrap_forward(struct data_ring*, char *iterator);

/* Returns parameter iterator wrapped at the array begin. */

static char *wrap_backward(struct data_ring*, char *iterator);

void data_ring_init(struct data_ring *object)
{
    object->array_length = object->container.element_size
                            * (object->container.capacity + 1);

    object->array_end = object->container.array + object->array_length;

    object->begin = object->container.array;
    object->end   = object->begin;
    object->end_minus_one = object->array_end - object->container.element_size;
}

size_t data_ring_size(struct data_ring *object)
{
    char const *array = object->container.array;

    size_t byte_size;

    if (object->begin <= object->end) {
        byte_size = object->end - object->begin;
    } else {
        size_t begin_size = object->array_end - object->begin;
        size_t   end_size = object->end - array;

        byte_size = begin_size + end_size;
    }

    return byte_size / object->container.element_size;
}

bool data_ring_empty(struct data_ring *object)
{
    return object->begin == object->end;
}

bool data_ring_full(struct data_ring *object)
{
    if (object->begin == object->container.array)
        return object->end == object->array_end;

    return object->end == object->begin - object->container.element_size;
}

void *data_ring_begin(struct data_ring *object)
{
    return object->begin;
}

void *data_ring_end(struct data_ring *object)
{
    return object->end;
}

void *data_ring_end_minus_one(struct data_ring *object)
{
    return object->end_minus_one;
}

void data_ring_push_front(struct data_ring *object, void const *element)
{
    object->begin -= object->container.element_size;
    object->begin  = wrap_backward(object, object->begin);

    memcpy(object->begin, element, object->container.element_size);
}

void data_ring_pop_front(struct data_ring *object)
{
    object->begin += object->container.element_size;
    object->begin  = wrap_forward(object, object->begin);
}

void data_ring_push_back(struct data_ring *object, void const *element)
{
    memcpy(object->end, element, object->container.element_size);

    object->end += object->container.element_size;
    object->end  = wrap_forward(object, object->end);

    object->end_minus_one += object->container.element_size;
    object->end_minus_one  = wrap_forward(object, object->end_minus_one);
}

void data_ring_pop_back(struct data_ring *object)
{
    object->end -= object->container.element_size;
    object->end  = wrap_backward(object, object->end);

    object->end_minus_one -= object->container.element_size;
    object->end_minus_one  = wrap_backward(object, object->end_minus_one);
}

static char *wrap_forward(struct data_ring *object, char *iterator)
{
    if (iterator == object->array_end)
        return object->container.array;

    return iterator;
}

static char *wrap_backward(struct data_ring *object, char *iterator)
{
    char const *array = object->container.array;

    if (iterator < array)
        return iterator + object->array_length;

    return iterator;
}
