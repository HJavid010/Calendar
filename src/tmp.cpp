#include <iostream>
#include <ctime>
#include "date.hpp"
#include "date.cpp"

int main()
{
    _date hi;
    time_t t;
    time(&t);
    int a = (t / (3600 * 24));
    for (int i = 1389; i < 1460; i++)
    {
        if (calendars.ghamari.IsLeapYear(i))
            std::cout << i << std::endl;
    }
    for (int i = 1;; i++)
    {
        hi = DayToDate(a - i, calendars.shamsi);
        std::cout << hi.year << "/" << hi.month << "/" << hi.day<<std::endl;
    }}