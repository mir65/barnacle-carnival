#define F_CPU 16000000

#include <stdbool.h>
#include <dev/delay.h>
#include <dev/interrupt.h>
#include <dev/pin.h>
#include <dev/axis.h>
#include <dev/servo.h>
#include <dev/timer.h>

int main()
{
    dev_timer_init();
    dev_interrupt_init();
    dev_axis_module_init();
    dev_servo_module_init();

    struct dev_axis axis1 = { .signal_pin = 13 };
    dev_axis_init(&axis1);

    struct dev_axis axis2 = { .signal_pin = 12 };
    dev_axis_init(&axis2);

    struct dev_servo servo = { .pin = 23 };
    dev_servo_init(&servo);

    for (;;) {
        dev_servo_angle(&servo, dev_axis_read(&axis1) - 1000);
        dev_delay_ms(10);
    }
}
