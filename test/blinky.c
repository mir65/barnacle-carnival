#define F_CPU 16000000

#include <dev/delay.h>
#include <dev/pin.h>

int main()
{
    dev_pin_output(22);

    for (;;) {
        dev_pin_write(22, false);
        dev_delay_ms(100);

        dev_pin_write(22, true);
        dev_delay_ms(100);
    }
}
