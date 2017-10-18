#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <data/vector.h>
#include "pin.h"

/* A callback bound to a pin number */

struct callback_binding {
    uint_fast8_t number;
    void (*callback)();
};

/* Returns a pointer to the callback_binding with pin number in a vector.
 *
 * If not found, returns NULL.
 */

static struct callback_binding* find_number(struct data_vector *vector,
                                            uint_fast8_t number);

/* Returns a pointer to the callback_binding with callback in a vector.
 *
 * If not found, returns NULL.
 */

static struct callback_binding* find_callback(struct data_vector *vector,
                                              void (*callback)());

/* Calls the callback for each callback_binding in a vector. */

static void call_all(struct data_vector *vector);

/* Backing arrays for callback vectors */

static struct callback_binding arrays[3][8];

/* Vectors of callbacks, indexed by port number */

static struct data_vector binding_vectors[3] = {
    {
        .array = &arrays[0],
        .element_size = sizeof(struct callback_binding),
        .capacity = 8
    },
    {
        .array = &arrays[1],
        .element_size = sizeof(struct callback_binding),
        .capacity = 8
    },
    {
        .array = &arrays[2],
        .element_size = sizeof(struct callback_binding),
        .capacity = 8
    }
};

void dev_interrupt_init()
{
    for (size_t i = 0; i < 3; ++i)
        data_vector_init(&binding_vectors[i]);

    /* Enable pin change interrupts on all ports */
    PCICR |= (1 << PCIE2);
    PCICR |= (1 << PCIE1);
    PCICR |= (1 << PCIE0);

    /* Enable interrupts globally */
    sei();
}

void dev_interrupt_bind(uint_fast8_t number, void (*callback)())
{
    char port_number = dev_pins[number].port_number;
    struct data_vector *bindings = &binding_vectors[port_number];

    if (find_callback(bindings, callback) != NULL)
        return;

    struct callback_binding binding = { number, callback };
    data_vector_push_back(bindings, &binding);

    *dev_pins[number].int_mask |= (1 << (dev_pins[number].int_bit));
}

void dev_interrupt_unbind(uint_fast8_t number)
{
    char port_number = dev_pins[number].port_number;
    struct data_vector *bindings = &binding_vectors[port_number];

    struct callback_binding *binding = find_number(bindings, number);

    if (binding == NULL)
        return;

    *dev_pins[number].int_mask &= ~(1 << (dev_pins[number].int_bit));

    data_vector_erase_at(bindings, binding);
}

struct callback_binding* find_number(struct data_vector *vector,
                                     uint_fast8_t number)
{
    struct callback_binding *begin = data_vector_begin(vector);
    struct callback_binding *end   = data_vector_end(vector);

    for (struct callback_binding *i = begin; i != end; ++i)
        if (i->number == number)
            return i;

    return NULL;
}

struct callback_binding* find_callback(struct data_vector *vector,
                                       void (*callback)())
{
    struct callback_binding *begin = data_vector_begin(vector);
    struct callback_binding *end   = data_vector_end(vector);

    for (struct callback_binding *i = begin; i != end; ++i)
        if (i->callback == callback)
            return i;

    return NULL;
}

void call_all(struct data_vector *vector)
{
    struct callback_binding *i = data_vector_begin(vector);

    while (i != data_vector_end(vector))
        (*i++).callback();
}

ISR(BADISR_vect)
{
    for (;;);
}

ISR(PCINT0_vect)
{
    call_all(&binding_vectors[0]);
}

ISR(PCINT1_vect)
{
    call_all(&binding_vectors[1]);
}

ISR(PCINT2_vect)
{
    call_all(&binding_vectors[2]);
}
