#ifndef EVENT_H
#define EVENT_H 1
#include "date.hpp"
#include <iostream>

struct event
{
    // items with id = 0 are not used yet;
    unsigned long long int id = 0;
    std::string title;
    std::string description;
    date date;
};

#endif