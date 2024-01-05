#include "date.hpp"
int _date::IsNotVaild()
{
    if (year < 1970)
        return 1;
    if (month > 12)
        return 2;
    if (day > 31)
        return 3;
    return 0;
}

int _date::Equal(_date second_date)

{
    if (year != second_date.year || month != second_date.month || day != second_date.day)
        return 0;
    return 1;
}


_date DayToDate(unsigned long long int)
{
    _date date;
    return date;
}

int _calendar::IsLeapYear(int year)
{
    switch (id)
    {
    case 0:
        if (year % 100 && !(year % 4))
            return 1;
        break;
    case 1:
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
