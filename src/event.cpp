#include "event.hpp"

int event::Equal(event second_event)
{
    if (!date.Equal(second_event.date))
        return 0;
    return 1;
}