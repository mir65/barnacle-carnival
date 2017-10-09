#ifndef DEV_AXIS_H
#define DEV_AXIS_H

#include <stdint.h>

/* Input hobby PWM signal */

struct dev_axis {
    /* Hobby PWM signal input
     *
     * Digital input with interrupt support on change
     */

    uint8_t signal_pin;

    /* Private */

    /* Most recent rising edge timestamp
     *
     * Access from interrupt only
     */

    uint_fast16_t rise_time;

    /* Most recent time difference between rising and falling edge
     *
     * Shared access from interrupt and main thread
     *
     * Assumption: atomic
     */

    uint_fast16_t volatile high_time;
};

/* Initializes pins and interrupts. */

void dev_axis_init(struct dev_axis*);

/* Returns the signal value.
 *
 * Return value is in range [0, 1000].
 */

int_fast16_t dev_axis_value(struct dev_axis*);

#endif
