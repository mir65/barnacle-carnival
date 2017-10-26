#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "pin.h"
#include "timer.h"

/* Initializes 8-bit timer 0. */

static void init_timer0();

/* Initializes 16-bit timer 1. */

static void init_timer1();

/* Function to be called when an output compare match occurs on timer 1.
 *
 * One function for each output compare.
 *
 */

static void (*match_callback0)();
static void (*match_callback1)();

uint_fast16_t dev_time()
{
    return TCNT1;
}

void dev_timer_init()
{
    init_timer0();
    init_timer1();
}

void dev_timer_duty_cycle(uint_fast8_t number, uint_fast8_t duty)
{
    *dev_pins[number].output_compare = duty;
}

void dev_timer_schedule_match(uint_fast8_t instance, uint_fast16_t time)
{
    switch (instance) {
        case 0:
            OCR1A += time;
            break;
        case 1:
            OCR1B += time;
            break;
    }
}

void dev_timer_match_bind(uint_fast8_t instance, void (*callback)())
{
    switch (instance) {
        case 0:
            match_callback0 = callback;

            /* output compare match interrupt enable A */
            TIMSK1 |= (1 << OCIE1A);

            break;
        case 1:
            match_callback1 = callback;

            /* output compare match interrupt enable B */
            TIMSK1 |= (1 << OCIE1B);

            break;
    }
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
    TCCR0A |=  (1 << COM0B1);
    TCCR0A &= ~(1 << COM0B0);

    /* clock source prescaler 1 */
    TCCR0B &= ~(1 << CS02);
    TCCR0B &= ~(1 << CS01);
    TCCR0B |=  (1 << CS00);
}

void init_timer1()
{
    /* normal counter waveform generation mode */
    TCCR1B &= ~(1 << WGM12);
    TCCR1A &= ~(1 << WGM11);
    TCCR1A &= ~(1 << WGM10);

    /* clock source prescaler 8 */
    TCCR1B &= ~(1 << CS12);
    TCCR1B |=  (1 << CS11);
    TCCR1B &= ~(1 << CS10);

    /* initialize output compares to zero */
    OCR1A = 0;
    OCR1B = 0;
}

ISR(TIMER1_COMPA_vect)
{
    match_callback0();
}

ISR(TIMER1_COMPB_vect)
{
    match_callback1();
}
