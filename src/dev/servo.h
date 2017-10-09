#ifndef DEV_SERVO_H
#define DEV_SERVO_H

#include <stdint.h>

/* Servo motor */

struct dev_servo {
    /* Hobby PWM signal output
     *
     * Digital output
     */

    uint8_t pin;
};

/* Initializes pins */

void dev_servo_init(struct dev_servo*);

/* Sets the angle setpoint.
 *
 * Parameter setpoint uses the full range of the integral type.
 */

void dev_servo_angle(struct dev_servo*, int_fast16_t setpoint);

#endif
