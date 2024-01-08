#include "event.hpp"

_events events;

int _event::Occur(_date &second_date)
{
    if (date.day == second_date.day && date.month == second_date.month && date.year == second_date.year)
        return 1;
    return 0;
}

int _weekly_event::Occur(int &second_weekday)
{
    if (weekday == second_weekday)
        return 1;
    return 0;
}

int _monthly_event::Occur(int &second_day)
{
    if (day == second_day)
        return 1;
    return 0;
}

int _yearly_event::Occur(int &second_day, int &second_month)
{
    if (day == second_day && month == second_month)
        return 1;
    return 0;
}

int _event::IsVaild()
{
    if (title.length() != 0)
        return 1;
    return 0;
}

void _event_list::Sort()
{
    int sorted = 0;
    _event *tmp;
    while (!sorted)
    {

        sorted = 1;
        for (int i = 0; i < size - 1; i++)
        {
            if (event_ptr[i] > event_ptr[i + 1])
            {
                sorted = 0;
                tmp = event_ptr[i];
                event_ptr[i] = event_ptr[i + 1];
                event_ptr[i + 1] = tmp;
            }
        }
    }
    return;
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
    if (index < 0 || index > size)
        return 1;
    size--;
    for (int i = index; i < size; i++)
    {
        event_ptr[i] = event_ptr[i + 1];
    }
    return 0;
}
