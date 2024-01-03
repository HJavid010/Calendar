#ifndef EVENT_H
# define EVENT_H 1
#include "date.h"
#include <iostream>

struct event
{
    unsigned long long int id;
    std::string title;
    std::string description;
    unsigned int year,month,day;
    date date;
};


#endif