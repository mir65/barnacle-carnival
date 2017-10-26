#include <stdint.h>
#include <util/atomic.h>
#include <data/vector.h>
#include "interrupt.h"
#include "pin.h"
#include "timer.h"
#include "servo.h"

/* Applies a transition and schedules the next. */

static void on_match();

static struct dev_servo *array[4];

static struct data_vector servos = {
    .array = array,
    .element_size = sizeof(struct dev_servo*),
    .capacity = 4
};

static struct dev_servo **current;
static struct dev_servo **last;

static uint16_t remaining_period_time;

void dev_servo_module_init()
{
    data_vector_init(&servos);

    current = data_vector_begin(&servos);
    remaining_period_time = 40000;

    dev_timer_match_bind(on_match);
}

void dev_servo_init(struct dev_servo *object)
{
    dev_pin_output(object->pin);
    data_vector_push_back(&servos, &object);
}

void dev_servo_angle(struct dev_servo *object, int_fast16_t setpoint)
{
    /* Map (-1500, 1500) onto (1500, 4500). */
    setpoint += 3000;

    ATOMIC_BLOCK(ATOMIC_FORCEON) { object->high_time = setpoint; };
}

void on_match()
{
    struct dev_servo **begin = data_vector_begin(&servos);
    struct dev_servo **end   = data_vector_end(&servos);

    if (current == begin)
        remaining_period_time = 40000;
    else
        dev_pin_write((*last)->pin, false);

    if (current == end) {
        dev_timer_schedule_match(remaining_period_time);
    } else {
        dev_timer_schedule_match((*current)->high_time);
        remaining_period_time -= (*current)->high_time;

        dev_pin_write((*current)->pin, true);
    }

    last = current++;

    if (current > end)
        current = begin;
}
