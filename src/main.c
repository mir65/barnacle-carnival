#include <stdint.h>
#include <ctrl.h>
#include <dev.h>

/* Mode of operation */

enum mode {
    /* Raw signal relay
     *
     * Steering axis controls front wheel steering directly.
     *
     * Velocity axis controls motor voltage directly.
     */
    mode_relay,

    /* Backup assist
     *
     * Steering axis controls the trailer angle setpoint.
     *
     * Velocity axis selects between fixed velocity setpoint or stopped.
     */
    mode_assist
};

/* Returns the next mode for parameter mode.
 *
 * Transitions loop through all possible modes.
 */

static enum mode next_mode(enum mode mode);

/* Runs one iteration of parameter mode. */

static void run_iteration(enum mode mode);

/* Copies each input signal to each output signal. */

static void relay();

int main()
{
    dev_init();
    ctrl_init();

    enum mode mode = mode_relay;

    uint16_t iteration_end = 0;
    uint16_t const period = 20000;

    for (;;) {
        if (dev_mode_request())
            mode = next_mode(mode);

        run_iteration(mode);

        while (dev_time() < iteration_end);
        iteration_end += period;
    }
}

enum mode next_mode(enum mode mode)
{
    switch (mode) {
        case mode_relay:  return mode_assist;
        case mode_assist: return mode_relay;
    }
}

void run_iteration(enum mode mode)
{
    switch (mode) {
        case mode_relay:
            relay();
            break;
        case mode_assist:
            ctrl_steering_iteration();
            ctrl_velocity_iteration();
            break;
    }
}

void relay()
{
    int_fast16_t steering = dev_steering_axis();
    int_fast16_t velocity = dev_velocity_axis();

    /* map (0, 2000) onto (-1000, 1000) */
    steering -= 1000;
    velocity -= 1000;

    /* map (-1000, 1000) onto (-250, 250) */
    velocity /= 4;

    /* map (-1000, 1000) onto (-1500, 1500) */
    steering = steering * 3 / 2;

    dev_steer(steering);
    dev_motor_output(velocity);
}
