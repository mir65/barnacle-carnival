#ifndef DEV_SERIAL_H
#define DEV_SERIAL_H

/* Initializes USART transmitter. */

void dev_serial_module_init();

/* Transmits parameter string synchronously.
 *
 * Blocks until last character has been written to the TX buffer.
 */

void dev_serial_tx(char const *string);

#endif
