#include "pin.h"
#include <stdlib.h>
#include <avr/io.h>

/* Attributes of a pin */

struct pin {
    /* Direction register */
    char volatile *direction;

    /* Port register */

    char volatile *port;

    /* Pin register */

    char volatile *pin;

    /* Relevant bit in those registers*/

    char bit;
};

/* Information about pins, indexed by pin number */

static struct pin const pins[] = {
    /* 0-7 */
    { &DDRB, &PORTB, &PINB, PB0 },
    { &DDRB, &PORTB, &PINB, PB1 },
    { &DDRB, &PORTB, &PINB, PB2 },
    { &DDRB, &PORTB, &PINB, PB3 },
    { &DDRB, &PORTB, &PINB, PB4 },
    { &DDRB, &PORTB, &PINB, PB5 },
    { &DDRB, &PORTB, &PINB, PB6 },
    { &DDRB, &PORTB, &PINB, PB7 },

    /* 8-15 */
    { &DDRC, &PORTC, &PINC, PC0 },
    { &DDRC, &PORTC, &PINC, PC1 },
    { &DDRC, &PORTC, &PINC, PC2 },
    { &DDRC, &PORTC, &PINC, PC3 },
    { &DDRC, &PORTC, &PINC, PC4 },
    { &DDRC, &PORTC, &PINC, PC5 },
    { &DDRC, &PORTC, &PINC, PC6 },
    {  NULL,   NULL,  NULL,   0 },

    /* 16-23 */
    { &DDRD, &PORTD, &PIND, PD0 },
    { &DDRD, &PORTD, &PIND, PD1 },
    { &DDRD, &PORTD, &PIND, PD2 },
    { &DDRD, &PORTD, &PIND, PD3 },
    { &DDRD, &PORTD, &PIND, PD4 },
    { &DDRD, &PORTD, &PIND, PD5 },
    { &DDRD, &PORTD, &PIND, PD6 },
    { &DDRD, &PORTD, &PIND, PD7 }
};

void dev_pin_input(uint_fast8_t number)
{
    *pins[number].direction &= ~(1 << (pins[number].bit));
    *pins[number].port &= ~(1 << (pins[number].bit));
}

void dev_pin_output(uint_fast8_t number)
{
    *pins[number].direction |= (1 << (pins[number].bit));
}

bool dev_pin_read(uint_fast8_t number)
{
    return *pins[number].pin & (1 << (pins[number].bit));
}

void dev_pin_write(uint_fast8_t number, bool value)
{
    if (value)
        *pins[number].port |=  (1 << (pins[number].bit));
    else
        *pins[number].port &= ~(1 << (pins[number].bit));
}
