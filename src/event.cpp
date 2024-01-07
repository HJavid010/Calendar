#include "event.hpp"

_events events;

int _event::Occur(_date &second_date)
{
    if (date.day == second_date.day && date.month == second_date.month && date.year == second_date.year)
        return 1;
    return 0;
}
