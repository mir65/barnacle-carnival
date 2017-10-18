#define F_CPU 16000000

#include <stdbool.h>
#include <avr/io.h>
#include "dev/delay.h"
#include "dev/pin.h"

int main()
{
    // OC0A pin
    dev_pin_output(22);

    // fast PWM waveform generation mode
    TCCR0B &= ~(1 << WGM02);
    TCCR0A |=  (1 << WGM01);
    TCCR0A |=  (1 << WGM00);

    // non-inverting compare
    TCCR0A |=  (1 << COM0A1);
    TCCR0A &= ~(1 << COM0A0);

    // clock source prescaler 1
    TCCR0B &= ~(1 << CS02);
    TCCR0B &= ~(1 << CS01);
    TCCR0B |=  (1 << CS00);

    for (unsigned char x = 0;; ++x) {
        char y;

        if (x < 128)
            y = x;
        else
            y = 255 - x;

        y *= 2;

        OCR0A = y;
        dev_delay_ms(2);
    }
}
