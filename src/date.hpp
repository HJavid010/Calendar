#ifndef DATE_H
#define DATE_H 1
#include <ctime>
#include <iostream>

// _ddate is days passed from 1990-1-1 and is used for date calculation and storing.

// _date is used to store a date from any kind and functions to easily vaildate it or check equality with another.
struct _date
{
    unsigned int year, month, day;
    int IsNotVaild();
    int Equal(_date);
};

struct _weekday
{
    int number;
    std::string ToGeorgian();
    std::string ToShamsi();
    std::string ToGamari();
    int FirstRecurrence(int);
};

struct _months
{
    std::string name[12];
    int size[12];
};



_date DayToDate(unsigned long long int);
_date SystemDate();

#endif