#define F_CPU 16000000

#include <dev/delay.h>
#include <dev/pin.h>
#include <dev/timer.h>

int main()
{
    dev_pin_output(22);

    dev_timer_init();

    for (unsigned char x = 0;; ++x) {
        char y;

        if (x < 128)
            y = x;
        else
            y = 255 - x;

        dev_timer_duty_cycle(22, 2 * y);

        dev_delay_ms(2);
    }
}
