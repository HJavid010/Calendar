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
