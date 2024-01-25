#include "date.hpp"

int _calendar::IsLeapYear(int year)
{
    switch (id)
    {
    case 0:
        switch (year % 33)
        {
        case 30:
        case 26:
        case 22:
        case 17:
        case 13:
        case 9:
        case 5:
        case 1:
            return 1;
            break;
        default:
            break;
        }
        break;
    case 1:
        if ((year % 100 != 0 || year % 400 == 0) && year % 4 == 0)
            return 1;
        break;
    case 2:
        switch (year % 30)
        {
        case 29:
        case 26:
        case 24:
        case 21:
        case 18:
        case 16:
        case 13:
        case 10:
        case 7:
        case 5:
        case 2:
            return 1;
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }

    return 0;
}

int Weekday(int ddate, _calendar &calendar)
{
    return (ddate % 7 + 7 + calendar.weekday_begin) % 7;
}

_date DayToDate(int ddate, _calendar &calendar)
{
    _date out_date = calendar.origin;
    if (ddate < 0)
        return out_date;
    int days;
    days = calendar.year_size;
    if (calendar.IsLeapYear(out_date.year))
        days++;
    while (ddate > days)
    {
        ddate -= days;
        out_date.year++;
        days = calendar.year_size + calendar.IsLeapYear(out_date.year);
    };
    days = out_date.month_size(calendar);

    while (ddate > days)
    {
        ddate -= days;
        out_date.month++;
        if (out_date.month == 13)
        {
            out_date.year++;
            out_date.month = 1;
        }
        days = out_date.month_size(calendar);
    }
    out_date.day += ddate;
    if (out_date.day > out_date.month_size(calendar))
    {
        out_date.day -= out_date.month_size(calendar);
        out_date.month++;
    }
    if (out_date.month == 13)
    {
        out_date.year++;
        out_date.month = 1;
    }
    return out_date;
}
int DateToDay(_date date, _calendar &calendar)
{
    int ddate = 0;
    ddate += (calendar.IsLeapYear(date.year) && (date.month > calendar.leap_month));

    while (date.year > calendar.origin.year)
    {
        date.year--;
        ddate += calendar.year_size + (calendar.IsLeapYear(date.year));
    }
    while (date.month > calendar.origin.month)
    {
        date.month--;
        ddate += calendar.month_size[date.month - 1];
    }
    while (date.month < calendar.origin.month)
    {
        ddate -= calendar.month_size[date.month - 1];
        date.month++;
    }
    ddate += (date.day - calendar.origin.day);

    return ddate;
}

int SystemDDate()
{
    time_t t;
    time(&t);
    return t / (24 * 60 * 60);
}

int _date::IsVaild(_calendar &calendar)
{
    if (calendar.origin.year - year > 69 || month > 12 || month < 1 || day > month_size(calendar) || day < 1)
        return 0;
    return 1;
}

int _date::IsEqual(_date &second_date)
{
    if (day == second_date.day && month == second_date.month && year == second_date.year)
        return 1;
    return 0;
}

int _date::IsAfter(_date &second_date)
{

    if (year > second_date.year)
        return 1;
    else if (year == second_date.year && month > second_date.month)
        return 1;
    else if (year == second_date.year && month == second_date.month && day > second_date.day)
        return 1;
    else
        return 0;
}

int _date::month_size(_calendar &calendar)
{
    return calendar.month_size[month - 1] + (calendar.IsLeapYear(year) && calendar.leap_month == month);
}

std::string _date::String(_calendar &calendar)
{

    std::string output;

    output.append(std::to_string(day));
    output += ' ';
    output.append(calendar.month_name[month - 1]);
    output += ' ';
    output.append(std::to_string(year));

    return output;
}
