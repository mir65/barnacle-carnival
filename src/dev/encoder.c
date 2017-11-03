#include <stdbool.h>
#include <stdint.h>
#include <util/atomic.h>
#include <data/vector.h>
#include "interrupt.h"
#include "pin.h"
#include "encoder.h"

/* Updates all encoder counts based on input signal changes. */

static void on_change();

/* Returns the state formatted for object->prev_state. */

static uint_fast8_t read_state(struct dev_encoder*);

/* Maps current state to next state, indexed by current state.
 *
 *   00 -> 01
 *   01 -> 11
 *   11 -> 10
 *   10 -> 00
 */

static uint_fast8_t next_state[4] = { 1, 3, 0, 2 };

/* Maps current state to previous state, indexed by current state.
 *
 *   00 -> 10
 *   01 -> 00
 *   11 -> 01
 *   10 -> 11
 */

static uint_fast8_t prev_state[4] = { 2, 0, 3, 1 };

static struct encoder *array[4];

static struct data_vector encoders = {
    .array = array,
    .element_size = sizeof(struct encoder*),
    .capacity = 4
};

void dev_encoder_module_init()
{
    data_vector_init(&encoders);
}

void dev_encoder_init(struct dev_encoder *object)
{
    object->prev_state = read_state(object);
    object->count = 0;

    data_vector_push_back(&encoders, &object);

    dev_pin_input(object->signal1_pin);
    dev_pin_input(object->signal2_pin);

    dev_interrupt_bind(object->signal1_pin, on_change);
    dev_interrupt_bind(object->signal2_pin, on_change);
}

int_fast16_t dev_encoder_count(struct dev_encoder *object)
{
    int_fast16_t count;

    ATOMIC_BLOCK(ATOMIC_FORCEON) { count = object->count; }

    return count;
}

void on_change()
{
    struct dev_encoder **i   = data_vector_begin(&encoders);
    struct dev_encoder **end = data_vector_end(&encoders);

    for (; i != end; ++i) {
        struct dev_encoder *j = *i;

        uint_fast8_t state = read_state(j);

        bool moved_forward  = state == next_state[j->prev_state];
        bool moved_backward = state == prev_state[j->prev_state];

        if (moved_forward)
            ++j->count;
        if (moved_backward)
            --j->count;

        j->prev_state = state;
    }
}

uint_fast8_t read_state(struct dev_encoder *object)
{
    uint_fast8_t state = (dev_pin_read(object->signal1_pin) << 1) |
                         (dev_pin_read(object->signal2_pin) << 0);
}
