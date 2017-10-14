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

    uint16_t timer = 0; /* TODO */
    uint16_t iteration_end = 0;
    const uint16_t period = 0;

    for (;;) {
        if (dev_mode_request())
            mode = next_mode(mode);

        run_iteration(mode);

        while (timer < iteration_end);
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
    int16_t steering = dev_steering_axis();
    int16_t velocity = dev_velocity_axis();

    /* unimplemented - translate */

    dev_steer(steering);
    dev_motor_output(velocity);
}
