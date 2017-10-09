#include "pid.h"

/* Returns parameter x constrained to the range between parameter min and
 * parameter max, inclusive.
 */

static int_fast16_t constrain(int_fast16_t x,
                              int_fast16_t min,
                              int_fast16_t max);

void ctrl_pid_init(struct ctrl_pid *object)
{
    object->error = 0;
    object->sum   = 0;
}

int_fast16_t ctrl_pid_iteration(struct ctrl_pid *object, int_fast16_t error)
{
    error = constrain(error, -1024, 1024);

    /* Range [-2048, 2048] */
    int_fast16_t change = error - object->error;

    object->error = error;
    object->sum  += error;

    object->sum = constrain(object->sum, -object->sum_limit,
                                          object->sum_limit);

    /* Range 2**29 * [-1, 1] */
    int_fast32_t p_term = (int_fast32_t) object->kp * error;

    /* Range 2**29 * [-1, 1] */
    int_fast32_t i_term = (int_fast32_t) object->ki * object->sum;

    /* Range 2**29 * [-1, 1] */
    int_fast32_t d_term = (int_fast32_t) object->kd * change;

    /* Range 2**29 * [-3, 3] */
    int_fast32_t response = -(p_term + i_term + d_term);

    return response;
}

static int_fast16_t constrain(int_fast16_t x,
                              int_fast16_t min,
                              int_fast16_t max)
{
    if      (x < min) x = min;
    else if (x > max) x = max;

    return x;
}
