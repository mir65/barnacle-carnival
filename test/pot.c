#define F_CPU 16000000

#include <stdio.h>
#include <dev.h>
#include <dev/pot.h>
#include <dev/serial.h>

int main()
{
    dev_serial_module_init();
    dev_pot_module_init();

    struct dev_pot pot = {
        .pin = 0
    };

    dev_pot_init(&pot);

    int_fast16_t last_count = 0;

    for (;;) {
        dev_delay_ms(100);

        char line[81];

        int_fast16_t count = dev_pot_position(&pot);

        if (count == last_count)
            continue;

        last_count = count;

        sprintf(line, "%4d\n", count);

        dev_tx(line);
    }
}
