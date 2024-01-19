#include "event.hpp"

#include <fstream>

int _event::IsVaild()
{
    if (title.length() != 0)
        return 1;
    return 0;
}

int _event::Occur(_date &second_date, _calendar &calendar)
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
    return search_array_size;
}

int _event_list::SearchByDate(_date second_date, int search_array[], _calendar &calendar)
{
    int search_array_size = 0;
    for (int i = 0; i < size; i++)
    {
        if (event_ptr[i]->Occur(second_date, calendar))
        {
            search_array[search_array_size] = i;
            search_array_size++;
        }
    }
    return search_array_size;
}

int IsInString(std::string big_string, std::string small_string)
{
    int big_string_size = big_string.length();
    int small_string_size = small_string.length();
    int found;
    for (int i = 0; i < big_string_size - small_string_size + 1; i++)
    {
        found = true;
        for (int ii = 0; ii < small_string_size; ii++)
        {
            if (big_string[i + ii] != small_string[ii])
            {
                found = false;
                break;
            }
        }
        if (found)
            break;
    }
    return found;
}

int _event_list::EventListSaveToFile(std::string filename)
{
    std::ofstream file(filename, std::ios_base::out);
    for (int i = 0; i < size; i++)
    {
        file << "\"" << ReplaceQuotationToBackslashQ(event_ptr[i]->title) << "\", \"" << ReplaceQuotationToBackslashQ(event_ptr[i]->description) << ", " << event_ptr[i]->id << ", " << event_ptr[i]->date.day << ", " << event_ptr[i]->date.month << ", " << event_ptr[i]->date.year;
    }
    return 0;
}
std::string ReplaceQuotationToBackslashQ(std::string text)
{
    return text;
}
