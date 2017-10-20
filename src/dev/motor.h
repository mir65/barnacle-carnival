#ifndef DEV_MOTOR_H
#define DEV_MOTOR_H

#include <stdint.h>

/* DC motor */

struct dev_motor {
    /* Controls the output voltage direction.
     *
     * True is forward, false is backward.
     *
     * Digital output
     */

    uint8_t direction_pin;

    /* Controls the output voltage magnitude.
     *
     * PWM output
     */

    uint8_t voltage_pin;
};

/* Initializes pins.
 *
 * Sets the voltage to a default of zero.
 */

void dev_motor_init(struct dev_motor*);

/* Sets the output voltage.
 *
 * Parameter voltage is in range [-255, 255]. Positive is forward, negative is
 * backward.
 */

void dev_motor_voltage(struct dev_motor*, int_fast16_t value);

#endif
