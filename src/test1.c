#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>

int test = 7;

ISR(PCINT2_vect)
{
    int x = 0;
    ++x;
}

int main()
{
    int x;

    for (size_t i = 0; i < 10; ++i) ++x;

    SREG &= 1<<7;
}
