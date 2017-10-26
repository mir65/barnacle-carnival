#include <stdbool.h>
#include <util/atomic.h>
#include <data/vector.h>
#include <dev.h>
#include "interrupt.h"
#include "pin.h"
#include "timer.h"
#include "axis.h"

/* Finds the pin that changed and updates the relevant axis. */

static void on_edge();

static struct dev_axis *array[4];

static struct data_vector axes = {
    .array = array,
    .element_size = sizeof(struct dev_axis*),
    .capacity = 4
};

void dev_axis_module_init()
{
    data_vector_init(&axes);
}

void dev_axis_init(struct dev_axis *object)
{
    object->state = false;
    object->rise_time = 0;
    object->high_time = 0;

    data_vector_push_back(&axes, &object);

    dev_pin_input(object->signal_pin);
    dev_interrupt_bind(object->signal_pin, on_edge);
}

int_fast16_t dev_axis_read(struct dev_axis *object)
{
    uint16_t high_time;

    ATOMIC_BLOCK(ATOMIC_FORCEON) { high_time = object->high_time; }

    /* Map (2000, 4000) onto (0, 2000). */
    high_time -= 2000;

    if (high_time <    0) high_time =    0;
    if (high_time > 2000) high_time = 2000;

    return high_time;
}

void on_edge()
{
    struct dev_axis **i   = data_vector_begin(&axes);
    struct dev_axis **end = data_vector_end(&axes);

    while (i != end) {
        struct dev_axis *j = *i;

        bool state = dev_pin_read(j->signal_pin);

        if (state != j->state) {
            j->state = state;

            if (state)
                j->rise_time = dev_time();
            else
                j->high_time = dev_time() - j->rise_time;
        }

        ++i;
    }
}
