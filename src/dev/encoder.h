#ifndef DEV_ENCODER_H
#define DEV_ENCODER_H

#include <stdint.h>

/* Incremental quadrature encoder */

struct dev_encoder {
    /* Signal pins
     *
     * Digital inputs with interrupt support on change
     */

    uint8_t signal1_pin;
    uint8_t signal2_pin;

    /* Private */

    /* Previous signal state
     *
     * Bit 1 from signal 1, bit 0 from signal 2
     *
     * Example:
     *
     *   signal 1 = true
     *   signal 2 = false
     *
     *     => 00000010
     *
     * Access from interrupt only
     */

    uint8_t prev_state;

    /* Most recent count
     *
     * Shared access from interrupt and main thread
     *
     * Assumption: atomic
     */

    int_fast16_t volatile count;
};

/* Initializes pins and interrupts. */

void dev_encoder_init(struct dev_encoder*);

/* Returns the count.
 *
 * Count is LSB.
 */

int_fast16_t dev_encoder_count(struct dev_encoder*);

#endif
