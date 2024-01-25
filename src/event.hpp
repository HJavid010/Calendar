#ifndef EVENT_H
#define EVENT_H 1

#include "string.hpp"
#include "date.hpp"
#include <iostream>
#include <fstream>

#define EVENT_LIST_SIZE 3000
#define EVENT_FILE "event.txt"

struct _event
{
    int id = 0;
    std::string title;
    std::string description;
    _date date;
    int ToggleDone();
    int IsVaild(_calendar &);
    int Occur(_date &second_date, _calendar &);
    int IsEvent();
    int IsTask();
    int IsTaskDone();
    std::string Type();
    std::string Status();
};

struct _event_list
{
    _event event[EVENT_LIST_SIZE];
    _event *event_ptr[EVENT_LIST_SIZE];
    int real_size = EVENT_LIST_SIZE;
    int size = 0;
    // didn't find a usecase for sort function
    int Sort();
    int Add(_event &, _calendar &);
    int Remove(int);
    int EventSearchByString(std::string, int[]);
    int TaskSearchByString(std::string, int[]);
    int EventsOccurOnDate(_date, int[], _calendar &);
    int TasksOccurOnDate(_date, int[], _calendar &);
    int EventsOccurAfter(_date, int[], _calendar &);
    int EventListSaveToFile(std::string filename = EVENT_FILE);
    int EventListLoadFromFile(_calendar &, std::string filename = EVENT_FILE);
};

#endif