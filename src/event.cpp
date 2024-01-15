#include "event.hpp"
#include "date.cpp"

int _event::IsVaild()
{
    if (title.length() != 0)
        return 1;
    return 0;
}

int _event::Occur(int id, _date &second_date, _calendar &calendar = calendars.shamsi)
{
    switch (id)
    {
    // specific date event
    case 0:
        return (date.day == second_date.day && date.month == second_date.month && date.year == second_date.year);
        break;
    // yearly event
    case 1:
        return (date.day == second_date.day && date.month == second_date.month && date.year <= second_date.year);
        break;
    // montly event
    case 2:
        return (date.day == second_date.day && date.month <= second_date.month && date.year <= second_date.year);
        break;
    // weakly event
    case 3:
        int ddate, second_ddate;
        ddate = DateToDay(this->date, calendar);
        second_ddate = DateToDay(second_date, calendar);
        return (ddate <= second_ddate && (ddate % 7 == second_ddate % 7));
        break;
    default:
        return 0;
        break;
    }
    return 0;
}

int _event_list::Add(_event &new_event)
{
    // list is full!
    if (size == real_size)
        return 1;
    if (!new_event.IsVaild())
        return 2;

    int occupied = 1;
    _event *ptr = event;
    while (occupied)
    {
        occupied = 0;
        for (int i = 0; i < real_size; i++)
        {
            if (event_ptr[i] == ptr)
            {
                occupied = 1;
                break;
            }
        }
        if (!occupied)
            break;
        ptr++;
    }
    event_ptr[size] = ptr;
    *ptr = new_event;
    size++;
    return 0;
}

int _event_list::Remove(int index)
{
    if (index < 0 || index > size - 1)
        return 1;
    size--;
    for (int i = index; i < size; i++)
    {
        event_ptr[i] = event_ptr[i + 1];
    }
    return 0;
}
