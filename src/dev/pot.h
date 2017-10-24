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
};

/* Initializes pins. */

void dev_pot_init(struct dev_pot*);

/* Returns the position.
 *
 * Return value is in range [0, 255].
 */

int_fast16_t dev_pot_position(struct dev_pot*);

#endif
