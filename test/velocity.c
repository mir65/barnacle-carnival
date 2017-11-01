#define F_CPU 16000000

#include <stdio.h>
#include <dev/delay.h>
#include <dev/encoder.h>
#include <dev/serial.h>
#include <dev/speedometer.h>
#include <dev/timer.h>

int main()
{
    dev_serial_module_init();
    dev_timer_init();
    dev_encoder_module_init();
    dev_speedometer_module_init();

    struct dev_encoder encoder1 = {
        .signal1_pin = 0,
        .signal2_pin = 0
    };

    struct dev_encoder encoder2 = {
        .signal1_pin = 0,
        .signal2_pin = 0
    };

    struct dev_speedometer speedometer1 = {
        .encoder = &encoder1
    };

    struct dev_speedometer speedometer2 = {
        .encoder = &encoder2
    };

    dev_encoder_init(&encoder1);
    dev_encoder_init(&encoder2);

    dev_speedometer_init(&speedometer1);
    dev_speedometer_init(&speedometer2);

    int_fast16_t last_velocity1 = 0;
    int_fast16_t last_velocity2 = 0;

    for (;;) {
        dev_delay_ms(100);

        char line[81];

        int_fast16_t velocity1 = dev_speedometer_read(&speedometer1);
        int_fast16_t velocity2 = dev_speedometer_read(&speedometer2);

        if (velocity1 == last_velocity1 && velocity2 == last_velocity2)
            continue;

        last_velocity1 = velocity1;
        last_velocity2 = velocity2;

        int_fast16_t sum = velocity1 + velocity2;

        sprintf(line, "%5d = %5d + %5d\n", sum, velocity1, velocity2);

        dev_serial_tx(line);
    }
}
