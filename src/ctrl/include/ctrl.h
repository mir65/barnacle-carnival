#ifndef CTRL_INTERFACE_H
#define CTRL_INTERFACE_H

/* Initializes the module. */

void ctrl_init();

/* Runs one iteration of the steering control loop. */

void ctrl_steering_iteration();

/* Runs one iteration of the velocity control loop. */

void ctrl_velocity_iteration();

#endif
