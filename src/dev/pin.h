#ifndef DEV_PIN_H
#define DEV_PIN_H

#include <stdbool.h>
#include <stdint.h>

/* Attributes of a pin */

struct pin {
    /* Digital I/O */

    /* Direction register */

    char volatile *direction;

    /* Port register */

    char volatile *port;

    /* Pin register */

    char volatile *pin;

    /* Relevant bit in those registers */

    char io_bit;

    /* Interrupt */

    /* Port number
     *
     * 0 is port B
     * 1 is port C
     * 2 is port D
     */

    char port_number;

    /* Mask register */

    char volatile *int_mask;

    /* Relevant bit in that register */

    char int_bit;

    /* Timer */

    /* Output compare register */

    char volatile *output_compare;
};

/* Information about pins, indexed by pin number
 *
 * Pin Numbers:
 *
 *    0 to  7: PB0-PB7
 *    8 to 14: PC0-PC6
 *   16 to 23: PD0-PD7
 */

struct pin const *dev_pins;

/* Configures the numbered pin as an input. */

void dev_pin_input(uint_fast8_t number);

/* Configures the numbered pin as an output. */

void dev_pin_output(uint_fast8_t number);

/* Returns the state of the numbered input pin.
 *
 * Return value is true/false for high/low.
 */

bool dev_pin_read(uint_fast8_t number);

/* Sets the state of the numbered output pin.
 *
 * Parameter value is true/false for high/low.
 */

void dev_pin_write(uint_fast8_t number, bool value);

#endif
