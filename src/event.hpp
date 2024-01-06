#ifndef EVENT_H
#define EVENT_H 1

#include "date.hpp"
#include <iostream>

#define EVENT_LIST_SIZE 300
struct _event
{
    // items with id = 0 are not used yet;
    unsigned long long int id = 0;
    std::string title;
    std::string description;
    int recurrence;
    unsigned long long int ddate;
    _weekday weekday;
    int Equal(_event);
};
struct _event_list
{
    _event event[EVENT_LIST_SIZE];
    int real_size = EVENT_LIST_SIZE;
    int size = 0;
    int sort(_event);
    int add(_event);
    int remove(_event);
    const int *search(std::string);
};

#endif