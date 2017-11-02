#include <avr/io.h>
#include <util/atomic.h>
#include <data/vector.h>
#include "pin.h"
#include "pot.h"

static struct dev_pot *array[4];

static struct data_vector pots = {
    .array = array,
    .element_size = sizeof(struct dev_pot*),
    .capacity = 4
};

/* Current instance being sampled */

static struct dev_pot *current;

void dev_pot_module_init()
{
    current = data_vector_begin(&pots);

    /* default to pin ADC0 */
    ADMUX = 0;

     /* prescaler 128 */
    ADCSRA = (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

    ADCSRB = 0;

     /* ADC enable */
    ADCSRA |= (1 << ADEN);

    /* start conversion */
    ADCSRA |= (1 << ADSC);
}

void dev_pot_init(struct dev_pot *object)
{
    dev_pin_input(object->pin);

    object->value = 0;

    ATOMIC_BLOCK(ATOMIC_FORCEON) {
        data_vector_push_back(&pots, &object);
    }
}

int_fast16_t dev_pot_position(struct dev_pot *object)
{
    int_fast16_t value;

    ATOMIC_BLOCK(ATOMIC_FORCEON) { value = object->value; };

    return value;
}

ISR(ADC_vect)
{
    if (!data_vector_empty(&pots))
        current++->value = ADC;

    if (current == data_vector_end(&pots))
        current = data_vector_begin(&pots);

    /* select pin to work on */
    ADMUX = current->pin - 8;

    /* start conversion */
    ADCSRA |= (1 << ADSC);
}
