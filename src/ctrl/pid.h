#ifndef CTRL_PID_H
#define CTRL_PID_H

#include <stdint.h>

/* PID controller
 *
 * Assumes fixed frequency updates.
 *
 * Does not use internal timers. Frequency affects tuning constants.
 */

struct ctrl_pid {
    /* Proportional tuning constant
     *
     * Must be in range [0, 2**19].
     */

    int_fast16_t kp;

    /* Integral tuning constant
     *
     * Must be in range [0, 1024].
     */

    int_fast16_t ki;

    /* Derivative tuning constant
     *
     * Must be in range [0, 2**18].
     */

    int_fast16_t kd;

    /* Maximum magnitude of the error sum
     *
     * Limits integral windup.
     *
     * Must be in range [0, 2**19].
     */

    int_fast16_t sum_limit;

    /* Private */

    /* Most recent error */

    int_fast16_t error;

    /* Running sum of all errors */

    int_fast16_t sum;
};

/* Initializes. */

void ctrl_pid_init(struct ctrl_pid*);

/* Runs one iteration.
 *
 * Parameter error introduces the error for this iteration.
 *
 * Returns the output response.
 *
 * Parameter error is clipped to range [-1024, 1024].
 */

int_fast16_t ctrl_pid_iteration(struct ctrl_pid*, int_fast16_t error);

#endif
