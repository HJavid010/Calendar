#include "date.hpp"
int date::IsNotVaild()
{
    if (year < 1970)
        return 1;
    if (month > 12)
        return 2;
    if (day > 31)
        return 3;
    return 0;
}

int date::Equal(date second_date)

{
    if (year != second_date.year || month != second_date.month || day != second_date.day)
        return 0;
    return 1;
}
/*
extern date gregorian_origin = {gregorian_origin.year = 1970,
                                gregorian_origin.month = 1,
                                gregorian_origin.day = 1};

extern date shamsi_origin = {shamsi_origin.year = 1348,
                                shamsi_origin.month = 10,
                                shamsi_origin.day = 11};

extern date ghamari_origin = {ghamari_origin.year = 1389,
                                ghamari_origin.month = 10,
                                ghamari_origin.day = 22};
*/
date DayToDate(unsigned long long int)
{
    date date;
    return date;
}

int calendar::IsLeapYear(int year)
{

    switch (id)
    {
    case 0:
        if (year % 100 && !(year % 4))
            return 1;
        break;
    case 1:
        int mod = year % 33;
        switch (mod)
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
        int mod = year % 30;
        switch (mod)
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
