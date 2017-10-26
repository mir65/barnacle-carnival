#ifndef DEV_SPEEDOMETER_H
#define DEV_SPEEDOMETER_H

#include <stdint.h>
#include <data/ring.h>
#include "encoder.h"

/* Update period in 2*microseconds */

#define DEV_SPEEDOMETER_PERIOD 20000

/* Number of periods across which to make distance comparisons */

#define DEV_SPEEDOMETER_WINDOW_LENGTH 10

/* Speedometer which polls encoder position
 *
 * Takes samples asynchronously at a fixed period. Makes distance comparisons
 * across a number of periods in order to increase resolution at the expense of
 * some sort of laggy effect.
 */

struct dev_speedometer {
    /* Encoder to poll
     *
     * Must already be initialized
     */

    struct dev_encoder *encoder;

    /* Private */

    /* Previous counts */

    int_fast16_t count_array[DEV_SPEEDOMETER_WINDOW_LENGTH + 2];
    struct data_ring count_buffer;
};

/* Initializes the module. */

void dev_speedometer_module_init();

/* Initializes pins. */

void dev_speedometer_init(struct dev_speedometer*);

/* Returns the velocity.
 *
 * Return value is LSB/(window_length*period) [TBD].
 */

int_fast16_t dev_speedometer_read(struct dev_speedometer*);

#endif
