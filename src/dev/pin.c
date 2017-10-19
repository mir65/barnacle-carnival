#include "pin.h"
#include <stdlib.h>
#include <avr/io.h>

/* Information about pins, indexed by pin number */

static struct pin const pins[] = {
    /* 0-7 */
    { &DDRB, &PORTB, &PINB, PB0, 0, &PCMSK0, PCINT0,    NULL },
    { &DDRB, &PORTB, &PINB, PB1, 0, &PCMSK0, PCINT1,    NULL },
    { &DDRB, &PORTB, &PINB, PB2, 0, &PCMSK0, PCINT2,    NULL },
    { &DDRB, &PORTB, &PINB, PB3, 0, &PCMSK0, PCINT3,    NULL },
    { &DDRB, &PORTB, &PINB, PB4, 0, &PCMSK0, PCINT4,    NULL },
    { &DDRB, &PORTB, &PINB, PB5, 0, &PCMSK0, PCINT5,    NULL },
    { &DDRB, &PORTB, &PINB, PB6, 0, &PCMSK0, PCINT6,    NULL },
    { &DDRB, &PORTB, &PINB, PB7, 0, &PCMSK0, PCINT7,    NULL },

    /* 8-15 */
    { &DDRC, &PORTC, &PINC, PC0, 1, &PCMSK1, PCINT8,    NULL },
    { &DDRC, &PORTC, &PINC, PC1, 1, &PCMSK1, PCINT9,    NULL },
    { &DDRC, &PORTC, &PINC, PC2, 1, &PCMSK1, PCINT10,   NULL },
    { &DDRC, &PORTC, &PINC, PC3, 1, &PCMSK1, PCINT11,   NULL },
    { &DDRC, &PORTC, &PINC, PC4, 1, &PCMSK1, PCINT12,   NULL },
    { &DDRC, &PORTC, &PINC, PC5, 1, &PCMSK1, PCINT13,   NULL },
    { &DDRC, &PORTC, &PINC, PC6, 1, &PCMSK1, PCINT14,   NULL },
    {  NULL,   NULL,  NULL,   0, 0,    NULL,       0,   NULL },

    /* 16-23 */
    { &DDRD, &PORTD, &PIND, PD0, 2, &PCMSK2, PCINT16,   NULL },
    { &DDRD, &PORTD, &PIND, PD1, 2, &PCMSK2, PCINT17,   NULL },
    { &DDRD, &PORTD, &PIND, PD2, 2, &PCMSK2, PCINT18,   NULL },
    { &DDRD, &PORTD, &PIND, PD3, 2, &PCMSK2, PCINT19,   NULL },
    { &DDRD, &PORTD, &PIND, PD4, 2, &PCMSK2, PCINT20,   NULL },
    { &DDRD, &PORTD, &PIND, PD5, 2, &PCMSK2, PCINT21, &OCR0B },
    { &DDRD, &PORTD, &PIND, PD6, 2, &PCMSK2, PCINT22, &OCR0A },
    { &DDRD, &PORTD, &PIND, PD7, 2, &PCMSK2, PCINT23,   NULL }
};

struct pin const *dev_pins = pins;

void dev_pin_input(uint_fast8_t number)
{
    *pins[number].direction &= ~(1 << (pins[number].io_bit));
    *pins[number].port &= ~(1 << (pins[number].io_bit));
}

void dev_pin_output(uint_fast8_t number)
{
    *pins[number].direction |= (1 << (pins[number].io_bit));
}

bool dev_pin_read(uint_fast8_t number)
{
    return *pins[number].pin & (1 << (pins[number].io_bit));
}

void dev_pin_write(uint_fast8_t number, bool value)
{
    if (value)
        *pins[number].port |=  (1 << (pins[number].io_bit));
    else
        *pins[number].port &= ~(1 << (pins[number].io_bit));
}
