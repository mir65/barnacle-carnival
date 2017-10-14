/* TODO:
 *
 *  - Use pointer "iterator" instead of size.
 *  - Use memcpy() instead of char moves.
 *  - Cast void* to char* for arithmetic (standards compliance).
 */

#include <data/vector.h>

void data_vector_init(struct data_vector *object)
{
    object->size = 0;
}

size_t data_vector_size(struct data_vector *object)
{
    return object->size;
}

bool data_vector_empty(struct data_vector *object)
{
    return object->size == 0;
}

bool data_vector_full(struct data_vector *object)
{
    return object->size == object->capacity;
}

void *data_vector_begin(struct data_vector *object)
{
    return object->array;
}

void *data_vector_end(struct data_vector *object)
{
    return object->array + object->element_size * object->size;
}

void data_vector_push_back(struct data_vector *object, void const *element)
{
    if (data_vector_full(object))
        return;

    void *destination = object->array + object->element_size * object->size++;

    for (size_t i = 0; i < object->element_size; ++i)
        *((char*) destination++) = *((char*) element++);
}

void data_vector_pop_back(struct data_vector *object)
{
    --object->size;
}

void data_vector_erase_at(struct data_vector *object, void *iterator)
{
    void *source      = object->array + object->element_size * --object->size;
    void *destination = iterator;

    for (size_t i = 0; i < object->element_size; ++i)
        *((char*) destination++) = *((char*) source++);
}
