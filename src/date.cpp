#include "date.hpp"

struct _calendars
{
    _calendar shamsi{
        .id = 0,
        .origin{.year = 1348, .month = 10, .day = 11},
        .month_name = {"Farvardin", "Ordibehesht", "Khordad", "Tir", "Mordad", "Shahrivar", "Mehr", "Aban", "Azar", "Dey", "Bahman", "Esfand"},
        .month_size = {31, 31, 31, 31, 31, 31, 30, 30, 30, 30, 30, 29},
        .year_size = 365,
        .leap_month = 12};

    _calendar georgian{
        .id = 1,
        .origin{.year = 1970, .month = 1, .day = 1},
        .month_name = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"},
        .month_size = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
        .year_size = 365,
        .leap_month = 2};

    _calendar ghamari{
        .id = 2,
        .origin{.year = 1389, .month = 10, .day = 22},
        .month_name = {"al-Muharram", "Safar", "Rabi`al-Awwal", "Rabi`al-Thani", "Jumada`al-Ula", "Jumada`al-Thani", "Rajab", "Sha`ban", "Ramadan", "Shawwal", "Dhu`al-Qadah", "Dhu`al-Hijjah"},
        .month_size = {30, 29, 30, 29, 30, 29, 30, 29, 30, 29, 30, 29},
        .year_size = 355,
        .leap_month = 12};

} calendars;

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

_date DayToDate(int ddate, _calendar &calendar = calendars.shamsi)
{
    _date out_date = calendar.origin;
    int days;
    days = 0;
    for (int i = out_date.month - 1; i < 12; i++)
        days += calendar.month_size[i];
    if (calendar.IsLeapYear(out_date.year))
        days++;
    while (ddate > days)
    {
        ddate -= calendar.year_size +calendar.IsLeapYear(out_date.year);
        out_date.year++;
        days = 0;
        for (int i = out_date.month - 1; i < 12; i++)
            days += calendar.month_size[i];
        if (calendar.IsLeapYear(out_date.year))
            days++;
    };
    days = calendar.month_size[out_date.month - 1];
    if (out_date.month == calendar.leap_month && calendar.IsLeapYear(out_date.year))
        days++;
    while (ddate > days)
    {
        ddate -= days;
        out_date.month++;
        days = calendar.month_size[out_date.month - 1];
        if (out_date.month == calendar.leap_month && calendar.IsLeapYear(out_date.year))
            days++;
    }
    out_date.day += ddate;
    return out_date;
}
