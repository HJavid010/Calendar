#include "event.hpp"

int _event::ToggleDone()
{
    switch (id)
    {
    case 4:
        id = 5;
        break;
    case 5:
        id = 4;
        break;
    default:
        return 1;
        break;
    }
    return 0;
}

int _event::IsVaild(_calendar &calendar)
{
    if (title.length() == 0 || !date.IsVaild(calendar))
        return 0;
    return 1;
}

int _event::Occur(_date &second_date, _calendar &calendar)
{
    switch (id)
    {
    // specific date event
    case 0:
    case 4:
    case 5:
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

int _event::IsEvent()
{
    switch (id)
    {
    case 0:
    case 1:
    case 2:
    case 3:
        return 1;
        break;
    }
    return 0;
}

int _event::IsTask()
{
    switch (id)
    {
    case 4:
    case 5:
        return 1;
        break;
    }
    return 0;
}

int _event::IsTaskDone()
{
    if (id == 5)
        return 1;
    return 0;
}

_date _event::FirstRecurrenceAfter(_date target_date, _calendar &calendar)
{
    _date new_date = calendar.origin;
    int ddate, target_ddate, new_ddate;

    switch (id)
    {
    case 1:
        new_date.day = date.day;
        new_date.month = date.month;
        new_date.year = target_date.year;
        if (new_date.IsAfter(target_date))
            break;
        new_date.year++;
        while (!new_date.IsVaild(calendar))
            new_date.year++;
        break;
    case 2:
        new_date.day = date.day;
        new_date.month = target_date.month;
        new_date.year = target_date.year;
        if (new_date.IsAfter(target_date))
            break;
        new_date.month++;
        while (!new_date.IsVaild(calendar))
        {
            new_date.month++;
            if (new_date.month > 12)
            {
                new_date.month = 1;
                new_date.year++;
            }
        }
        break;
    case 3:
        ddate = DateToDay(date, calendar);
        target_ddate = DateToDay(target_date, calendar);
        new_ddate = target_ddate + (ddate % 7 - target_ddate % 7 + 7) % 7;
        new_date = DayToDate(new_ddate, calendar);
        break;
    }
    return new_date;
}

std::string _event::Type()
{
    switch (id)
    {
    case 0:
    case 1:
    case 2:
    case 3:
        return "Event";
        break;
    case 4:
    case 5:
        return "Task";
        break;
    }
    return "";
}

std::string _event::Status()
{
    switch (id)
    {
    case 0:
        return "Specific date";
        break;
    case 1:
        return "Yearly";
        break;
    case 2:
        return "Monthly";
        break;
    case 3:
        return "Weekly";
        break;
    case 4:
        return "Unfinished";
        break;
    case 5:
        return "Done";
        break;
    }
    return "";
}

int _event_list::Sort()
{
    int sorted = false;
    while (!sorted)
    {
        sorted = true;
        for (int i = 0; i < size - 1; i++)
        {
            if (event_ptr[i]->date.IsAfter(event_ptr[i + 1]->date))
            {
                sorted = false;
                _event *tmp_event_ptr;
                tmp_event_ptr = event_ptr[i];
                event_ptr[i] = event_ptr[i + 1];
                event_ptr[i + 1] = tmp_event_ptr;
            }
        }
    }
    return 0;
}

int _event_list::Add(_event &new_event, _calendar &calendar)
{
    // list is full!
    if (size == real_size)
        return 1;
    if (!new_event.IsVaild(calendar))
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
    Sort();
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

int _event_list::EventSearchByString(std::string search_string, int search_array[])
{
    int search_array_size = 0;
    for (int i = 0; i < size; i++)
    {
        if (event_ptr[i]->IsEvent())
        {
            if (IsInString(event_ptr[i]->title, search_string) || IsInString(event_ptr[i]->description, search_string))
            {
                search_array[search_array_size] = i;
                search_array_size++;
            }
        }
    }
    int sorted = false;
    while (!sorted)
    {
        sorted = true;
        for (int i = 0; i < search_array_size - 1; i++)
        {
            if (event_ptr[search_array[i]]->title.compare(event_ptr[search_array[i + 1]]->title) > 0)
            {
                sorted = false;
                int tmp;
                tmp = search_array[i];
                search_array[i] = search_array[i + 1];
                search_array[i + 1] = tmp;
            }
        }
    }
    return search_array_size;
}
int _event_list::TaskSearchByString(std::string search_string, int search_array[])
{
    int search_array_size = 0;
    for (int i = 0; i < size; i++)
    {
        if (event_ptr[i]->IsTask())
        {
            if (IsInString(event_ptr[i]->title, search_string) || IsInString(event_ptr[i]->description, search_string))
            {
                search_array[search_array_size] = i;
                search_array_size++;
            }
        }
    }
    int sorted = false;
    while (!sorted)
    {
        sorted = true;
        for (int i = 0; i < search_array_size - 1; i++)
        {
            if (event_ptr[search_array[i]]->title.compare(event_ptr[search_array[i + 1]]->title) > 0)
            {
                sorted = false;
                int tmp;
                tmp = search_array[i];
                search_array[i] = search_array[i + 1];
                search_array[i + 1] = tmp;
            }
        }
    }
    return search_array_size;
}
int _event_list::EventsOccurOnDate(_date date, int search_array[], _calendar &calendar)
{
    int search_array_size = 0;
    for (int i = 0; i < size; i++)
    {
        if (event_ptr[i]->IsEvent() && event_ptr[i]->Occur(date, calendar))
        {
            search_array[search_array_size] = i;
            search_array_size++;
        }
    }
    return search_array_size;
}

int _event_list::TasksOccurOnDate(_date date, int search_array[], _calendar &calendar)
{
    int search_array_size = 0;
    for (int i = 0; i < size; i++)
    {
        if (event_ptr[i]->IsTask() && event_ptr[i]->Occur(date, calendar))
        {
            search_array[search_array_size] = i;
            search_array_size++;
        }
    }
    return search_array_size;
}

int _event_list::EventsOccurAfter(_date date, int search_array[], _calendar &calendar)
{
    int search_array_size = 0;
    _date search_array_dates[size];
    for (int i = 0; i < size; i++)
    {
        if (event_ptr[i]->IsEvent())
        {
            if (date.IsAfter(event_ptr[i]->date))
            {
                if (event_ptr[i]->id != 0)
                {
                    search_array_dates[search_array_size] = event_ptr[i]->FirstRecurrenceAfter(date, calendar);
                    search_array[search_array_size] = i;
                    search_array_size++;
                }
            }
            else if (event_ptr[i]->date.IsAfter(date))
            {
                search_array_dates[search_array_size] = event_ptr[i]->date;
                search_array[search_array_size] = i;
                search_array_size++;
            }
        }
    }
    int sorted = false;
    while (!sorted)
    {
        sorted = true;
        for (int i = 0; i < search_array_size - 1; i++)
        {
            if (search_array_dates[i].IsAfter(search_array_dates[i + 1]))
            {
                sorted = false;
                _date tmp_date;
                tmp_date = search_array_dates[i];
                search_array_dates[i] = search_array_dates[i + 1];
                search_array_dates[i + 1] = tmp_date;
                int tmp;
                tmp = search_array[i];
                search_array[i] = search_array[i + 1];
                search_array[i + 1] = tmp;
            }
        }
    }
    return search_array_size;
}

int _event_list::TasksLate(_date date, int search_array[], _calendar &calendar)
{
    int search_array_size = 0;
    bool done = false;
    for (int i = 0; i < size; i++)
    {
        if (event_ptr[i]->id == 4)
        {
            if (date.IsAfter(event_ptr[i]->date))
            {
                search_array[search_array_size] = i;
                search_array_size++;
            }
            else
            {
                done = true;
                break;
            }
        }
        if (done)
            break;
    }
    return search_array_size;
}

int _event_list::TasksOccurAfter(_date date, int search_array[], _calendar &calendar)
{
    int search_array_size = 0;
    for (int i = 0; i < size; i++)
    {
        if (event_ptr[i]->IsTask())
        {
            if (event_ptr[i]->date.IsAfter(date))
            {
                if (event_ptr[i]->date.IsAfter(date))
                {
                    search_array[search_array_size] = i;
                    search_array_size++;
                }
            }
        }
    }
    return search_array_size;
}

int _event_list::EventListSaveToFile(std::string filename)
{
    std::ofstream file(filename, std::ios::out);
    if (file.is_open())
    {
        for (int i = 0; i < size; i++)
        {
            file << "\"" << StandardToRegex(event_ptr[i]->title) << "\", \"" << StandardToRegex(event_ptr[i]->description) << "\", " << event_ptr[i]->id << ", " << event_ptr[i]->date.year << ", " << event_ptr[i]->date.month << ", " << event_ptr[i]->date.day << std::endl;
        }
        file.close();
        return 0;
    }
    return 1;
}

int _event_list::EventListLoadFromFile(_calendar &calendar, std::string filename)
{
    std::ifstream file(filename, std::ios::in);
    if (file.is_open())
    {
        std::string line;
        int line_error = 0;
        while (std::getline(file, line))
        {
            _event new_event;
            int list_size, expected_size = 6;
            std::string csjson[expected_size];
            list_size = LineToStringList(line, csjson, expected_size);
            if (list_size != expected_size)
            {
                line_error++;
                continue;
            }
            new_event.title = RemoveQuotation(csjson[0]);
            new_event.description = RemoveQuotation(csjson[1]);
            new_event.id = atoi(csjson[2].c_str());
            new_event.date.year = atoi(csjson[3].c_str());
            new_event.date.month = atoi(csjson[4].c_str());
            new_event.date.day = atoi(csjson[5].c_str());
            if (Add(new_event, calendar) != 0)
                line_error++;
        }
        file.close();
        return line_error;
    }
    return -1;
}