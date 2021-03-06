#define F_CPU 16000000
#define BAUD 57600

#include <avr/io.h>
#include <util/atomic.h>
#include <util/setbaud.h>

// Writes a character to the TX buffer.

static void put_character(char c);

void dev_serial_module_init()
{
    ATOMIC_BLOCK(ATOMIC_FORCEON) {
        UBRR0H = UBRRH_VALUE;
        UBRR0L = UBRRL_VALUE;

#if USE_2X
        UCSR0A |= (1 << U2X0);
#else
        UCSR0A &= ~(1 << U2X0);
#endif

        UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);
        UCSR0B |= (1 << TXEN0);
    }
}

void dev_tx(char const *string)
{
    char const *c = string;

    while (*c != '\0') {
        if (*c == '\n')
            put_character('\r');

        put_character(*c++);
    }
}

static void put_character(char c)
{
    /* wait for empty transmit buffer */
    while (!(UCSR0A & (1 << UDRE0)));

    /* write to TX buffer */
    UDR0 = c;
}
