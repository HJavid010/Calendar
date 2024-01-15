#include "event.hpp"


int _event::IsVaild()
{
    if (title.length() != 0)
        return 1;
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
    if (index < 0 || index > size)
        return 1;
    size--;
    for (int i = index; i < size; i++)
    {
        event_ptr[i] = event_ptr[i + 1];
    }
    return 0;
}
