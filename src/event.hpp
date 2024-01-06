#ifndef EVENT_H
#define EVENT_H 1

#include "date.hpp"
#include <iostream>

#define EVENT_LIST_SIZE 300
struct _event
{
    std::string title;
    std::string description;
    _date date;
    int Occur(_date &second_date);
};

struct _weekly_event
{
    std::string title;
    std::string description;
    int weekday;
    int Occur(int &second_weekday);
};
struct _monthly_event
{
    std::string title;
    std::string description;
    int day;
    int Occur(int &second_day);
};
struct _yearly_event
{
    std::string title;
    std::string description;
    int recurrence;
    int day;
    int month;
    int Occur(int &second_day, int &second_month);
};
struct _event_list
{
    _event event[EVENT_LIST_SIZE];
    _event *event_ptr = {0};
    int real_size = EVENT_LIST_SIZE;
    int size = 0;
    int sort(_event);
    int add(_event);
    int remove(_event);
    _event *search(std::string);
};

struct _weekly_event_list
{
    _event event[EVENT_LIST_SIZE];
    _event *event_ptr = {0};
    int real_size = EVENT_LIST_SIZE;
    int size = 0;
    int sort(_event);
    int add(_event);
    int remove(_event);
    _event *search(std::string);
};

struct _monthly_event_list
{
    _event event[EVENT_LIST_SIZE];
    _event *event_ptr = {0};
    int real_size = EVENT_LIST_SIZE;
    int size = 0;
    int sort(_event);
    int add(_event);
    int remove(_event);
    _event *search(std::string);
};

struct _yearly_event_list
{
    _event event[EVENT_LIST_SIZE];
    _event *event_ptr = {0};
    int real_size = EVENT_LIST_SIZE;
    int size = 0;
    int sort(_event);
    int add(_event);
    int remove(_event);
    _yearly_event *search(std::string);
};
#endif