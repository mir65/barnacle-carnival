#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>

//
//int test = 7;
//
//ISR(PCINT2_vect)
//{
//    int x = 0;
//    ++x;
//}

int main()
{
    //int x;

    //for (size_t i = 0; i < 10; ++i) ++x;

    //SREG &= 1<<7;

    // output
    DDRD |= (1<<PD6);

    for (;;) {
        _delay_ms(3000);

        // low
        PORTD &= ~(1<<PD6);

        _delay_ms(3000);

        // high
        PORTD |= 1<<PD6;
    }
}
