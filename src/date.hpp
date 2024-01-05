#ifndef DATE_H
#define DATE_H 1
#include <ctime>
#include <iostream>

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
    _date FirstRecurrence(_date);
};

struct _months
{
    std::string name[12];
    int size[12];
};
struct _calendar
{
    unsigned int id;
    _date origin;
    _months months;
    int IsLeapYear(int year);
};

struct _calendars
{
    _calendar gregorian;
    _calendar shamsi;
    _calendar ghamari;
};

_date DayToDate(unsigned long long int);
_date SystemDate();

#endif