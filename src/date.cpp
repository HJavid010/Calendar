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
