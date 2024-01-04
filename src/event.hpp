#ifndef EVENT_H
#define EVENT_H 1

#include "date.hpp"
#include <iostream>

#define EVENT_LIST_SIZE 300
struct event
{
    // items with id = 0 are not used yet;
    unsigned long long int id = 0;
    std::string title;
    std::string description;
    int recurrence;
    struct date date;
    struct weekday weekday;
    int Equal(event);
};
struct event_list
{
    struct event event[EVENT_LIST_SIZE];
    int real_size = EVENT_LIST_SIZE;
    int size = 0;
    int sort(struct event);
    int add(struct event);
    int remove(struct event);
    const int* search(std::string);
};

#endif