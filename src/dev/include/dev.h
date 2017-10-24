#ifndef DEV_INTERFACE_H
#define DEV_INTERFACE_H

#include <stdbool.h>
#include <stdint.h>

/* Initializes the module. */

void dev_init();

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
 * Return value is in range [-127, 127].
 */

int_fast16_t dev_trailer_angle();

/* Returns the current time in 2*microseconds.
 *
 * Overflows.
 */

uint_fast16_t dev_time();

#endif
