#ifndef DEV_TIMER_H
#define DEV_TIMER_H

#include <stdint.h>

/* Initializes all timers */

void dev_timer_init();

/* Sets the PWM duty cycle for a numbered pin.
 *
 * Only supports pins 21 and 22. :-)
 */

void dev_timer_duty_cycle(uint_fast8_t number, uint_fast8_t duty);

/* Schedules an output compare match in this amount of time after the previous
 * match.
 *
 * Parameter instance is 0 or 1.
 *
 * Parameter time is 2*microseconds.
 */

void dev_timer_schedule_match(uint_fast8_t instance, uint_fast16_t time);

/* Binds a match callback, scheduled by dev_timer_schedule_match().
 *
 * Parameter instance is 0 or 1.
 */

void dev_timer_match_bind(uint_fast8_t instance, void (*callback)());

#endif
