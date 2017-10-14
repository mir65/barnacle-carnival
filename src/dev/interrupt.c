#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <data/vector.h>

struct pin {
    /* Port number
     *
     *   0 is port B
     *   1 is port C
     *   2 is port D
     */

    char port;

    /* Mask register */

    char volatile *mask;

    /* Relevant bit in that register */

    char bit;
};

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

/* Information about pins, indexed by pin number */

static struct pin const pins[] = {
    /* 0-7 */
    { 0, &PCMSK0, PCINT0  },
    { 0, &PCMSK0, PCINT1  },
    { 0, &PCMSK0, PCINT2  },
    { 0, &PCMSK0, PCINT3  },
    { 0, &PCMSK0, PCINT4  },
    { 0, &PCMSK0, PCINT5  },
    { 0, &PCMSK0, PCINT6  },
    { 0, &PCMSK0, PCINT7  },

    /* 8-15 */
    { 1, &PCMSK1, PCINT8  },
    { 1, &PCMSK1, PCINT9  },
    { 1, &PCMSK1, PCINT10 },
    { 1, &PCMSK1, PCINT11 },
    { 1, &PCMSK1, PCINT12 },
    { 1, &PCMSK1, PCINT13 },
    { 1, &PCMSK1, PCINT14 },
    { 0,    NULL,       0 },

    /* 16-23 */
    { 2, &PCMSK2, PCINT16 },
    { 2, &PCMSK2, PCINT17 },
    { 2, &PCMSK2, PCINT18 },
    { 2, &PCMSK2, PCINT19 },
    { 2, &PCMSK2, PCINT20 },
    { 2, &PCMSK2, PCINT21 },
    { 2, &PCMSK2, PCINT22 },
    { 2, &PCMSK2, PCINT23 }
};

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
    char port = pins[number].port;
    struct data_vector *bindings = &binding_vectors[port];

    if (find_callback(bindings, callback) != NULL)
        return;

    struct callback_binding binding = { number, callback };
    data_vector_push_back(bindings, &binding);

    *pins[number].mask |= (1 << (pins[number].bit));
}

void dev_interrupt_unbind(uint_fast8_t number)
{
    char port = pins[number].port;
    struct data_vector *bindings = &binding_vectors[port];

    struct callback_binding *binding = find_number(bindings, number);

    if (binding == NULL)
        return;

    *pins[number].mask &= ~(1 << (pins[number].bit));

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
