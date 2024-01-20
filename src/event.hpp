#ifndef EVENT_H
#define EVENT_H 1

#include "date.hpp"
#include <iostream>

#define EVENT_LIST_SIZE 300
#define EVENT_FILE "event.txt"

struct _event
{
    int id = 0;
    std::string title;
    std::string description;
    _date date;
    int IsVaild();
    int Occur(_date &second_date, _calendar &);
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
    int SearchByString(std::string, int[]);
    int SearchByDate(_date, int[], _calendar &);
    int EventListSaveToFile(std::string filename = EVENT_FILE);
};
std::string StandardToRegex(std::string);
int IsInString(std::string, std::string);

#endif