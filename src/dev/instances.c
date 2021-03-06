#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "axis.h"
#include "encoder.h"
#include "interrupt.h"
#include "motor.h"
#include "pin.h"
#include "pot.h"
#include "serial.h"
#include "servo.h"
#include "speedometer.h"
#include "sticky.h"
#include "timer.h"

static struct dev_axis steering_axis = { .signal_pin = 10 };
static struct dev_axis velocity_axis = { .signal_pin = 11 };
static struct dev_axis     mode_axis = { .signal_pin = 12 };

/*
static struct dev_encoder encoders[] = {
    { .signal1_pin = 0, .signal2_pin = 0 },
    { .signal1_pin = 0, .signal2_pin = 0 }
};

static struct dev_speedometer speedometers[] = {
    { .encoder = &encoders[0] },
    { .encoder = &encoders[1] }
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

static struct dev_sticky mode_trigger;

static uint8_t const mode_light_pin = 14;

void dev_init()
{
    dev_interrupt_init();
    dev_timer_init();
    dev_axis_module_init();
    dev_servo_module_init();
    dev_encoder_module_init();
    dev_speedometer_module_init();
    dev_pot_module_init();
    dev_serial_module_init();

    dev_axis_init(&steering_axis);
    dev_axis_init(&velocity_axis);

    for (size_t i = 0; i < 2; ++i) {
        dev_motor_init(&motors[i]);
        dev_servo_init(&steering_servos[i]);
    }

    for (size_t i = 0; i < 2; ++i) {
        /* dev_encoder_init(&encoders[i]); */
        /* dev_speedometer_init(&speedometers[i]); */
    }

    /* dev_pot_init(&angle_pot); */

    dev_sticky_init(&mode_trigger);

    dev_pin_output(mode_light_pin);
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
    bool high = value > 1000;

    return dev_sticky_update(&mode_trigger, high);
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

void dev_mode_light(bool state)
{
    dev_pin_write(mode_light_pin, state);
}
