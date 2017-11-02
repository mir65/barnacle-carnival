#ifndef DEV_POT_H
#define DEV_POT_H

#include <stdint.h>

/* Potentiometer */

struct dev_pot {
    /* Analog input
     *
     * ADC pin
     */

    uint8_t pin;

    /* Private */

    /* Most recent ADC conversion
     *
     * Shared access from interrupt and main thread
     */

    uint_fast16_t value;
};

/* Initializes the module. */

void dev_pot_module_init();

/* Initializes pins. */

void dev_pot_init(struct dev_pot*);

/* Returns the position.
 *
 * Return value is in range [0, 1023].
 */

int_fast16_t dev_pot_position(struct dev_pot*);

#endif
