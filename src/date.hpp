#ifndef DATE_H
#define DATE_H 1
#include <ctime>
#include <iostream>

struct date
{
    unsigned int year, month, day;
    int IsNotVaild();
    int Equal(struct date);
};

struct weekday
{
    int number;
    std::string ToGeorgian();
    std::string ToShamsi();
    std::string ToGamari();
    date FirstRecurrence(date);
};


date DayToDate(unsigned long long int);
date SystemDate();

#endif