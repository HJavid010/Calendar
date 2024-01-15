#ifndef EVENT_H
#define EVENT_H 1

#include "date.hpp"
#include <iostream>

#define EVENT_LIST_SIZE 300
struct _event
{
    int id = 0;
    std::string title;
    std::string description;
    _date date;
    int IsVaild();
    int Occur(_date &second_date, int id);
};

struct _event_list
{
    _event event[EVENT_LIST_SIZE];
    _event *event_ptr[EVENT_LIST_SIZE];
    int real_size = EVENT_LIST_SIZE;
    int size = 0;
    // didn't find a usecase for sort function
    // void Sort();
    int Add(_event &);
    int Remove(int);
    int SearchByTitle(std::string, _event[]);
};

#endif