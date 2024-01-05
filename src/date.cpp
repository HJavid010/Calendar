#include "date.hpp"
int date::IsNotVaild()
{
    if (1970 > year > 2038)
        return 1;
    if (month > 12)
        return 1 ;
    if (day > 31)
        return 1 ;
    return 0;
}

int date::Equal(date second_date)

{
    if (year != second_date.year || month != second_date.month || day != second_date.day)
        return 0;
    return 1;
}
