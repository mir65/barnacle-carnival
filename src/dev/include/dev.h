#ifndef DEV_INTERFACE_H
#define DEV_INTERFACE_H

#include <stdbool.h>
#include <stdint.h>
#include "dev/delay.h"

/* Initializes the module. */

void dev_init();

/* Transmits parameter string on the serial device synchronously.
 *
 * Blocks until last character has been written to the TX buffer.
 */

void dev_tx(char const *string);

/* Returns the steering input axis position.
 *
 * Return value is in range [0, 2000].
 */

uint_fast16_t dev_steering_axis();

/* Returns the velocity input axis position.
 *
 * Return value is in range [0, 2000].
 */

uint_fast16_t dev_velocity_axis();

/* Returns true if a control mode change has been requested since last
 * invocation.
 */

bool dev_mode_request();

/* Sets the motor output voltage.
 *
 * Parameter voltage is in range [-255, 255]. Positive is forward, negative is
 * backward.
 */

void dev_motor_output(int_fast16_t voltage);

/* Returns the speedometer velocity at the rear wheels.
 *
 * Return value is LSB/s [TBD].
 */

int_fast16_t dev_velocity();

/* Sets the steering angle.
 *
 * Parameter angle is in range [-1000, 1000].
 */

void dev_steer(int_fast16_t angle);

/* Returns the trailer angle.
 *
 * Return value is in range [-511, 511].
 */

int_fast16_t dev_trailer_angle();

/* Returns the current time in 2*microseconds.
 *
 * Overflows.
 */

uint16_t dev_time();

/* Sets the mode light state.
 *
 * True is on, false is off.
 */

void dev_mode_light(bool state);

#endif
