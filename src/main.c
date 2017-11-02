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

/* Runs parameter function repeatedly.
 *
 * Parameter period controls the time between calls in 2*microseconds.
 *
 * If a call exceeds period, an error is reported with error_hang().
 */

static void periodically(uint16_t period, void (*function)());

/* Runs one iteration of parameter mode. */

static void iteration();

/* Copies each input signal to each output signal. */

static void relay();

/* Transmits message on the serial device, then blinks the mode light forever.
 */

static void error_hang(char const *message);

int main()
{
    dev_init();
    ctrl_init();

    periodically(20000, iteration);
}

void periodically(uint16_t period, void (*function)())
{
    uint16_t iteration_end = dev_time() + period;

    for (;;) {
        function();

        uint16_t wait_time = 0;

        while (dev_time() < iteration_end)
            ++wait_time;

        if (wait_time > period)
            error_hang("period exceeded");

        iteration_end += period;
    }
}

void iteration()
{
    static enum mode mode = mode_relay;

    if (dev_mode_request())
        mode = next_mode(mode);

    switch (mode) {
        case mode_relay:
            dev_mode_light(false);
            relay();
            break;
        case mode_assist:
            dev_mode_light(true);
            ctrl_steering_iteration();
            ctrl_velocity_iteration();
            break;
    }
}

enum mode next_mode(enum mode mode)
{
    switch (mode) {
        case mode_relay:  return mode_assist;
        case mode_assist: return mode_relay;
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

void error_hang(char const *message)
{
    dev_tx(message);
    dev_tx("\n");

    for (;;) {
        dev_mode_light(true);
        dev_delay_ms(500);

        dev_mode_light(false);
        dev_delay_ms(500);
    }
}
