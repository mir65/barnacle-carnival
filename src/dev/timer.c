#include <stdlib.h>
#include <avr/io.h>

/* Attributes of a pin */

struct pin {
    /* Output compare register */

    char volatile *output_compare;
};

/* Initializes 8-bit timer 0. */

static void init_timer0();

/* Initializes 16-bit timer 1. */

static void init_timer1();

/* Information about pins, indexed by pin number */

static struct pin const pins[] = {
    /* 0-7 */
    { NULL },
    { NULL },
    { NULL },
    { NULL },
    { NULL },
    { NULL },
    { NULL },
    { NULL },

    /* 8-15 */
    { NULL },
    { NULL },
    { NULL },
    { NULL },
    { NULL },
    { NULL },
    { NULL },
    { NULL },

    /* 16-23 */
    { NULL },
    { NULL },
    { NULL },
    { NULL },
    { NULL },
    { NULL },
    { &OCR0A },
    { NULL },
};

void dev_timer_init()
{
    init_timer0();
    init_timer1();
}

void dev_timer_duty_cycle(uint_fast8_t number, uint_fast8_t duty)
{
    *pins[number].output_compare = duty;
}

uint_fast16_t dev_timer_time()
{
    return TCNT1;
}

void init_timer0()
{
    /* fast PWM waveform generation mode */
    TCCR0B &= ~(1 << WGM02);
    TCCR0A |=  (1 << WGM01);
    TCCR0A |=  (1 << WGM00);

    /* non-inverting compare */
    TCCR0A |=  (1 << COM0A1);
    TCCR0A &= ~(1 << COM0A0);

    /* clock source prescaler 1 */
    TCCR0B &= ~(1 << CS02);
    TCCR0B &= ~(1 << CS01);
    TCCR0B |=  (1 << CS00);
}

void init_timer1()
{
    /* unimplemented */
}
