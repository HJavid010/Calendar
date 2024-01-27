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
    // id is used to seperate diffrent events and tasks
    // EVENTS
    // 0: specific date, 1: yearly, 2: monthly, 3: weekly
    // TASKS
    // 4: undone, 5: done
    int id = 0;

    std::string title;        // title can't be empty and should only be one line
    std::string description;  // title can be empty and multiline
    _date date;               // start date of repeating events or specific date for type 0 or tasks
    int ToggleDone();         // used to toggle status for tasks
    int IsVaild(_calendar &); // verify that can an event be added to the list or not

    // takes a date as argument and returns 1 if the event or tasks happens in the date
    int Occur(_date &second_date, _calendar &);
    int IsEvent();
    int IsTask();
    int IsTaskDone();
    _date FirstRecurrenceAfter(_date, _calendar &);
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
    int TasksLate(_date, int[], _calendar &);
    int TasksOccurAfter(_date, int[], _calendar &);
    int EventListSaveToFile(std::string filename = EVENT_FILE);
    int EventListLoadFromFile(_calendar &, std::string filename = EVENT_FILE);
};

#endif