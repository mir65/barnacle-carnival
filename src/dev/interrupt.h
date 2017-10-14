#ifndef DEV_INTERRUPT_H
#define DEV_INTERRUPT_H

/* Initializes the interrupt handling mechanism. */

void dev_interrupt_init();

/* Binds a callback to a numbered pin.
 *
 * If callback is already bound to a different pin from the same port, does
 * nothing.
 */

void dev_interrupt_bind(uint_fast8_t number, void (*callback)());

/* Removes the callback binding from a numbered pin.
 *
 * If no such binding exists, does nothing.
 */

void dev_interrupt_unbind(uint_fast8_t number);

#endif
