#include <stdbool.h>
#include <dev/pin.h>
#include <dev/interrupt.h>

void copy()
{
    bool input = dev_pin_read(13);
    dev_pin_write(22, input);
}

int main()
{
    dev_pin_input(13);
    dev_pin_output(22);

    dev_interrupt_init();
    dev_interrupt_bind(13, copy);

    for (;;);
}
