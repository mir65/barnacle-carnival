#include <stdint.h>
#include <dev.h>
#include "pid.h"

/* Returns the theoretical steering angle required to maintain parameter
 * trailer_angle.
 *
 * Parameter trailer_angle is trailer angle LSB.
 *
 * Return value is steering angle LSB.
 */

static int_fast16_t zero_steering(int_fast16_t trailer_angle);

static struct ctrl_pid pid = {
    .kp = 0,
    .ki = 0,
    .kd = 0,
    .sum_limit = 0
};

void ctrl_steering_init()
{
    ctrl_pid_init(&pid);
}

void ctrl_steering_iteration()
{
    int_fast16_t setpoint = dev_steering_axis();
    int_fast16_t measured = dev_trailer_angle();

    int_fast16_t error = measured - setpoint;

    int_fast16_t response = ctrl_pid_iteration(&pid, error);

    dev_steer(zero_steering(measured) + response);
}

int_fast16_t zero_steering(int_fast16_t trailer_angle)
{
    return trailer_angle;
}
