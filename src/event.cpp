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

    default:
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

    default:
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
    default:
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
    default:
        break;
    }
    return std::string();
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

int _event_list::SearchByString(std::string search_string, int search_array[])
{
    int search_array_size = 0;
    for (int i = 0; i < size; i++)
    {
        if (IsInString(event_ptr[i]->title, search_string) || IsInString(event_ptr[i]->description, search_string))
        {
            search_array[search_array_size] = i;
            search_array_size++;
        }
    }
    int sorted = false;
    while (!sorted)
    {
        sorted = true;
        for (int i = 0; i < size - 1; i++)
        {
            if (event_ptr[i]->title.compare(event_ptr[i + 1]->title) > 0)
            {
                sorted = false;
                _event *tmp_event_ptr;
                tmp_event_ptr = event_ptr[i];
                event_ptr[i] = event_ptr[i + 1];
                event_ptr[i + 1] = tmp_event_ptr;
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

int _event_list::OccurAfter(_date date, int search_array[])
{
    int search_array_size = 0;
    for (int i = 0; i < size; i++)
    {
        if (event_ptr[i]->date.IsEqual(date) || event_ptr[i]->date.IsAfter(date))
        {
            search_array[search_array_size] = i;
            search_array_size++;
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