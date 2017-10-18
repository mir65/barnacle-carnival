#ifndef DEV_DELAY_H
#define DEV_DELAY_H

#include <util/delay.h>

/* Blocks for a constant number of milliseconds. */

#define dev_delay_ms(x) _delay_ms(x)

#endif
