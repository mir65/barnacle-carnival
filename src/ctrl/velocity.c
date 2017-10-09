#include <stdint.h>
#include <dev.h>
#include "pid.h"

/* Fixed setpoint in 2*(encoder LSB)/s. */

static int_fast16_t const setpoint = 0;

static struct ctrl_pid pid = {
    .kp = 0,
    .ki = 0,
    .kd = 0,
    .sum_limit = 0
};

void ctrl_velocity_init()
{
    ctrl_pid_init(&pid);
}

void ctrl_velocity_iteration()
{
    int_fast16_t measured = dev_velocity();
    int_fast16_t error = measured - setpoint;

    int_fast16_t response = ctrl_pid_iteration(&pid, error);

    dev_motor_output(response);
}
