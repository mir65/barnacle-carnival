#ifndef DEV_TIMER_H
#define DEV_TIMER_H

/* Initializes all timers */

void dev_timer_init();

/* Sets the PWM duty cycle for a numbered pin.
 *
 * Only supports pins 21 and 22. :-)
 */

void dev_timer_duty_cycle(uint_fast8_t number, uint_fast8_t duty);

/* Returns the current time in 2*microseconds.
 *
 * Overflows.
 */

uint_fast16_t dev_timer_time();

/* Schedules an output compare match in this amount of time after the previous
 * match.
 *
 * Parameter time is 2*microseconds.
 */

void dev_timer_schedule_match(uint_fast16_t time);

/* Binds a match callback, scheduled by dev_timer_schedule_match(). */

void dev_timer_match_bind(void (*callback)());

#endif
