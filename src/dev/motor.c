#include <stdbool.h>
#include "pin.h"
#include "timer.h"
#include "motor.h"

void dev_motor_init(struct dev_motor *object)
{
    dev_pin_output(object->direction1_pin);
    dev_pin_output(object->direction2_pin);
    dev_pin_output(object->voltage_pin);
}

void dev_motor_voltage(struct dev_motor *object, int_fast16_t value)
{
    if      (value < -255) value = -255;
    else if (value >  255) value =  255;

    bool direction = value >= 0;

    dev_pin_write(object->direction1_pin,  direction);
    dev_pin_write(object->direction2_pin, !direction);
    dev_timer_duty_cycle(object->voltage_pin, value);
}
