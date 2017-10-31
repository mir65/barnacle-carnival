#include "dev/serial.h"

int main()
{
    dev_serial_module_init();

    dev_serial_tx("Hello world\n");

    for (;;);
}
