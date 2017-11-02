#define F_CPU 16000000

#include <stdio.h>
#include <dev.h>
#include <dev/encoder.h>
#include <dev/interrupt.h>
#include <dev/serial.h>

int main()
{
    dev_interrupt_init();
    dev_serial_module_init();
    dev_encoder_module_init();

    struct dev_encoder encoder1 = {
        .signal1_pin = 0,
        .signal2_pin = 0
    };

    struct dev_encoder encoder2 = {
        .signal1_pin = 0,
        .signal2_pin = 0
    };

    dev_encoder_init(&encoder1);
    dev_encoder_init(&encoder2);

    int_fast16_t last_count1 = 0;
    int_fast16_t last_count2 = 0;

    for (;;) {
        dev_delay_ms(100);

        char line[81];

        int_fast16_t count1 = dev_encoder_count(&encoder1);
        int_fast16_t count2 = dev_encoder_count(&encoder2);

        if (count1 == last_count1 && count2 == last_count2)
            continue;

        last_count1 = count1;
        last_count2 = count2;

        int_fast16_t sum = count1 + count2;

        sprintf(line, "%5d = %5d + %5d\n", sum, count1, count2);

        dev_tx(line);
    }
}
