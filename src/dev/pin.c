#include "pin.h"
#include <stdlib.h>
#include <avr/io.h>

/* Attributes of a pin */

struct pin {
    /* Direction register */

    char volatile *direction;

    /* Port register */

    char volatile *port;

    /* Relevant bit in those registers*/

    char bit;
};

/* Information about pins, indexed by pin number */

static struct pin const pins[] = {
    /* 0-7 */
    { &DDRB, &PORTB, PB0 },
    { &DDRB, &PORTB, PB1 },
    { &DDRB, &PORTB, PB2 },
    { &DDRB, &PORTB, PB3 },
    { &DDRB, &PORTB, PB4 },
    { &DDRB, &PORTB, PB5 },
    { &DDRB, &PORTB, PB6 },
    { &DDRB, &PORTB, PB7 },

    /* 8-15 */
    { &DDRC, &PORTC, PC0 },
    { &DDRC, &PORTC, PC1 },
    { &DDRC, &PORTC, PC2 },
    { &DDRC, &PORTC, PC3 },
    { &DDRC, &PORTC, PC4 },
    { &DDRC, &PORTC, PC5 },
    { &DDRC, &PORTC, PC6 },
    {  NULL,   NULL,   0 },

    /* 16-23 */
    { &DDRD, &PORTD, PD0 },
    { &DDRD, &PORTD, PD1 },
    { &DDRD, &PORTD, PD2 },
    { &DDRD, &PORTD, PD3 },
    { &DDRD, &PORTD, PD4 },
    { &DDRD, &PORTD, PD5 },
    { &DDRD, &PORTD, PD6 },
    { &DDRD, &PORTD, PD7 }
};

void dev_pin_input(uint_fast8_t number)
{
    *pins[number].direction &= ~(1 << (pins[number].bit));
}

void dev_pin_output(uint_fast8_t number)
{
    *pins[number].direction |= (1 << (pins[number].bit));
}

bool dev_pin_read(uint_fast8_t number)
{
    return *pins[number].port | (1 << (pins[number].bit));
}

void dev_pin_write(uint_fast8_t number, bool value)
{
    if (value)
        *pins[number].port |=  (1 << (pins[number].bit));
    else
        *pins[number].port &= ~(1 << (pins[number].bit));
}
