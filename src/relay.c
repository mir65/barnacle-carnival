#define F_CPU 16000000

#include <stdbool.h>
#include "dev/delay.h"
#include "dev/interrupt.h"
#include "dev/pin.h"
#include "dev/axis.h"
#include "dev/timer.h"

int main()
{
    dev_timer_init();
    dev_interrupt_init();
    dev_axis_module_init();

    struct dev_axis axis1 = { .signal_pin = 13 };
    dev_axis_init(&axis1);

    struct dev_axis axis2 = { .signal_pin = 12 };
    dev_axis_init(&axis2);

    dev_pin_output(22);
    dev_pin_output(21);

    for (;;) {
        dev_timer_duty_cycle(22, dev_axis_read(&axis1) / 8);
        dev_timer_duty_cycle(21, dev_axis_read(&axis2) / 8);
        dev_delay_ms(10);
    }
}
