#include <stdlib.h>
#include <util/atomic.h>
#include <data/ring.h>
#include <data/vector.h>
#include "speedometer.h"
#include "timer.h"

/* Updates all speedometers. */

static void update_all();

/* Samples a distance for the speedometer. */

static void update_one(struct dev_speedometer*);

static struct dev_speedometer *array[4];

static struct data_vector speedometers = {
    .array = array,
    .element_size = sizeof(struct dev_speedometer*),
    .capacity = 4
};

void dev_speedometer_module_init()
{
    data_vector_init(&speedometers);

    dev_timer_match_bind(1, update_all);
}

void dev_speedometer_init(struct dev_speedometer *object)
{
    struct data_ring *buffer = &object->count_buffer;

    buffer->container.array        = object->count_array;
    buffer->container.element_size = sizeof(int_fast16_t);
    buffer->container.capacity     = DEV_SPEEDOMETER_WINDOW_LENGTH + 1;

    data_ring_init(buffer);

    int_fast16_t initial_value = 0;

    for (size_t i = 0; i < DEV_SPEEDOMETER_WINDOW_LENGTH + 1; ++i)
        data_ring_push_back(buffer, &initial_value);
}

int_fast16_t dev_speedometer_read(struct dev_speedometer *object)
{
    int_fast16_t time0;
    int_fast16_t time1;

    ATOMIC_BLOCK(ATOMIC_FORCEON)
    {
        int_fast16_t *begin = data_ring_begin(&object->count_buffer);
        int_fast16_t *end   = data_ring_end_minus_one(&object->count_buffer);

        time0 = *begin;
        time1 = *end;
    }

    return time1 - time0;
}

void update_all()
{
    struct dev_speedometer *begin = data_vector_begin(&speedometers);
    struct dev_speedometer *end   = data_vector_end(&speedometers);

    for (struct dev_speedometer *i = begin; i != end; ++i)
        update_one(i);

    dev_timer_schedule_match(1, DEV_SPEEDOMETER_PERIOD);
}

void update_one(struct dev_speedometer *object)
{
    int_fast16_t count = dev_encoder_count(object->encoder);

    data_ring_pop_front(&object->count_buffer);
    data_ring_push_back(&object->count_buffer, &count);
}
