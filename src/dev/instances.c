#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "axis.h"
#include "encoder.h"
#include "interrupt.h"
#include "motor.h"
#include "pot.h"
#include "servo.h"
#include "timer.h"

static struct dev_axis steering_axis = { .signal_pin = 10 };
static struct dev_axis velocity_axis = { .signal_pin = 11 };
static struct dev_axis     mode_axis = { .signal_pin = 12 };

/*
static struct dev_encoder encoders[] = {
    { .signal1_pin = 0, .signal2_pin = 0 },
    { .signal1_pin = 0, .signal2_pin = 0 }
};
*/

static struct dev_motor motors[] = {
    { .direction1_pin = 19, .direction2_pin = 20, .voltage_pin = 21 },
    { .direction1_pin =  0, .direction2_pin = 23, .voltage_pin = 22 }
};

/*
static struct dev_pot angle_pot = { .pin = 0 };
*/

static struct dev_servo steering_servos[] = {
    { .pin = 8 },
    { .pin = 9 }
};

void dev_init()
{
    dev_interrupt_init();
    dev_timer_init();
    dev_axis_module_init();
    dev_servo_module_init();

    dev_axis_init(&steering_axis);
    dev_axis_init(&velocity_axis);

    for (size_t i = 0; i < 2; ++i) {
        /* dev_encoder_init(&encoders[i]); */
        dev_motor_init(&motors[i]);
        dev_servo_init(&steering_servos[i]);
    }

    /* dev_pot_init(&angle_pot); */
}

uint_fast16_t dev_steering_axis()
{
    return dev_axis_read(&steering_axis);
}

uint_fast16_t dev_velocity_axis()
{
    return dev_axis_read(&velocity_axis);
}

bool dev_mode_request()
{
    uint_fast16_t value = dev_axis_read(&mode_axis);

    // keep track of recent states
    //
    // has not been in triggered state for x time, return true
    //
    // unimplemented

    return false;
}

void dev_motor_output(int_fast16_t voltage)
{
    for (size_t i = 0; i < 2; ++i)
        dev_motor_voltage(&motors[i], voltage);
}

int_fast16_t dev_velocity()
{
    // make an encoder velocity device on top of encoder
    //
    // average values from left and right sides
    //
    // unimplemented

    return 0;
}

void dev_steer(int_fast16_t angle)
{
    for (size_t i = 0; i < 2; ++i)
        dev_servo_angle(&steering_servos[i], angle);
}

int_fast16_t dev_trailer_angle()
{
    int_fast16_t value = 0; /* dev_pot_position(&angle_pot); */

    // convert between pot position and angle
    //
    // probably just a linear function
    //
    // unimplemented

    return value;
}
