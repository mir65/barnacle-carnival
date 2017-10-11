#ifndef DEV_PIN_H
#define DEV_PIN_H

#include <stdbool.h>
#include <stdint.h>

/* Pin Numbers:
 *
 *    0 to  7: PB0-PB7
 *    8 to 14: PC0-PC6
 *   16 to 23: PD0-PD7
 */

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
