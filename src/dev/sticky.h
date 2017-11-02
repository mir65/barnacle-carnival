#ifndef DEV_STICKY_H
#define DEV_STICKY_H

#include <stdbool.h>
#include <stdint.h>

/* Sticky trigger */

struct dev_sticky {
    /* Private */

    /* Prevalence of a high or low signal
     *
     * Is incremented for high and decremented for low.
     */

    uint_fast8_t count;

    /* If we've already triggered during this high period */

    bool triggered;
};

/* Initializes. */

void dev_sticky_init(struct dev_sticky*);

/* Updates with data from the next cycle.
 *
 * Returns true if the trigger is activated his cycle.
 */

bool dev_sticky_update(struct dev_sticky*, bool high);

#endif
