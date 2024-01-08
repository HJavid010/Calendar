#ifndef DATE_H
#define DATE_H 1
#include <ctime>
#include <iostream>

// _ddate is days passed from 1990-1-1 and is used for date calculation and storing.

// _date is used to store a date from any kind and functions to easily vaildate it or check equality with another.
struct _date
{
    int year, month, day;
    int IsVaild();
    int Equal(_date &);
};

struct _weekday
{
    int number;
    std::string Togregorian();
    std::string ToShamsi();
    std::string ToGamari();
    int FirstRecurrence(int);
};


struct _calendar
    {
        unsigned int id;
        _date origin;
        std::string month_name[12];
        int month_size[12];
        int year_size;
        int leap_month;
        int origin_distance_begining;
        int IsLeapYear(int year);
    };

_date DayToDate(int ddate, _calendar &);
int DateToDay(_date,_calendar &);
_date SystemDate();

#endif