#include "event.hpp"

int _event::Equal(_event second_event)
{
    if (!date.Equal(second_event.date))
        return 0;
    return 1;
}