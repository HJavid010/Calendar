#ifndef DATE_H
#define DATE_H 1

#include <ctime>
#include <iostream>

// _ddate is days passed from calendar origin like 1990-1-1 or 1348-10-11 and is used for date calculation.

// we are defining calendar type because calendar struct and date struct depend on each other
struct _calendar;

// _date is used to store a date from any kind and functions to easily vaildate it or check equality with another.
struct _date
{
    int year, month, day;

    // IsVaild fucntion is used to vaildate a date with a predefined calendar
    int IsVaild(_calendar &);

    // IsEqual function takes a second date as argument and returns 1 if its equal else it will return 0
    int IsEqual(_date &);

    // IsAfter function takes a second date as argument and if the date is after the argument it will return 1 else it will return 0
    int IsAfter(_date &);

    // MonthSize function returns real month size that date is in it(considering leap years)
    int MonthSize(_calendar &);

    // return human readable date with month names in calendar
    std::string String(_calendar &);
};

// used to store needed calendar informations to be used for calculation of a date
// or month and weekdays names
struct _calendar
{
    std::string name;

    // to seperate calendars with each other when using calulator
    unsigned int id;

    // this date equals to origin epoc date
    _date origin;

    std::string month_name[12];
    int month_size[12];
    int year_size;
    int leap_month;

    // IsLeapYear funtion gets year as argument and returns 1 if its a leap year in this calnder
    int IsLeapYear(int year);

    std::string weekday_name[7];

    // to identify the first day of the week
    int weekday_begin;
};

// return a weekday that can be used with _calendar.weekday_name to get weekday name
int Weekday(int ddate, _calendar &);

// DayToDate function gets a ddate and returns a date according to calendar
_date DayToDate(int ddate, _calendar &);

// reverse of the function above
// DayToDate function gets a date and returns a ddate according to calendar
int DateToDay(_date, _calendar &);

// SystemDDate return system ddate 
int SystemDDate();

#endif