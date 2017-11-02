#include "sticky.h"

void dev_sticky_init(struct dev_sticky *object)
{
    object->count = 0;
    object->triggered = false;
}

bool dev_sticky_update(struct dev_sticky *object, bool high)
{
    uint_fast8_t last_count = object->count;

    if ( high && object->count < 100)
        ++object->count;
    if (!high && object->count > 0)
        --object->count;

    if (last_count == 0 && object->count == 0)
        object->triggered = false;

    if (!object->triggered && object->count == 100) {
        object->triggered = true;
        return true;
    }

    return false;
}
