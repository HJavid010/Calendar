#include "date.hpp"
#include "event.hpp"

#include <iostream>
#if defined _WIN32
#define CLEAR system("cls");
// clrscr(); // including header file : conio.h
#elif defined(__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
#define CLEAR system("clear");
// std::cout<< u8"\033[2J\033[1;1H"; //Using ANSI Escape Sequences
#elif defined(__APPLE__)
#define CLEAR system("clear");
#endif // defined _WIN32
struct _calendars
{
    _calendar shamsi{
        .name = "Shamsi",
        .id = 0,
        .origin{.year = 1348, .month = 10, .day = 11},
        .month_name = {"Farvardin", "Ordibehesht", "Khordad", "Tir", "Mordad", "Shahrivar", "Mehr", "Aban", "Azar", "Dey", "Bahman", "Esfand"},
        .month_size = {31, 31, 31, 31, 31, 31, 30, 30, 30, 30, 30, 29},
        .year_size = 365,
        .leap_month = 12,
        .weekday_name = {"Shanbeh", "Yekshanbeh", "Doshanbeh", "Seshanbeh", "Charshanbeh", "Panjshanbeh", "Jomeh"},
        .weekday_begin = 5};

    _calendar gregorian{
        .name = "Gregorian",
        .id = 1,
        .origin{.year = 1970, .month = 1, .day = 1},
        .month_name = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"},
        .month_size = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
        .year_size = 365,
        .leap_month = 2,
        .weekday_name = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"},
        .weekday_begin = 3};
} calendars;

_calendar *default_calendar = &calendars.shamsi;
_event_list events;
struct _today
{
    int ddate;
    _date shamsi;
    _date gregorian;
    void RegenerateDates();
} selected_day, today;

int start_page();

int main()
{
    today.ddate = SystemDDate();
    today.RegenerateDates();
    selected_day = today;
    int controller;
    while (true)
    {
        controller = start_page();
        switch (controller)
        {
        case 1:
            selected_day.ddate += 1;
            selected_day.RegenerateDates();
            break;
        case 2:
            selected_day.ddate -= 1;
            selected_day.RegenerateDates();
            break;
        case 3:
            return 0;
            break;

        default:
            break;
        }
    }
}

int start_page()
{
    std::string user_input;

    CLEAR
    // weekday
    std::cout << calendars.shamsi.name << ":    " << selected_day.shamsi.year << "/" << selected_day.shamsi.month << "/" << selected_day.shamsi.day << "\t" << calendars.shamsi.weekday_name[Weekday(selected_day.ddate, calendars.shamsi)] << std::endl;
    std::cout << calendars.gregorian.name << ": " << selected_day.gregorian.year << "-" << selected_day.gregorian.month << "-" << selected_day.gregorian.day << "\t" << calendars.gregorian.weekday_name[Weekday(selected_day.ddate, calendars.gregorian)] << std::endl;
    for (int i = 0; i < 30; i++)
        std::cout << "\033[32m*";
    std::cout << std::endl;
    std::cout << "\033[1;31;5m>>>\033[0m ";
    getline(std::cin, user_input);
    if (user_input == "N")
        return 1;
    if (user_input == "P")
        return 2;
    if (user_input == "Q")
        return 3;
    return 0;
}

void _today::RegenerateDates()
{
    shamsi = DayToDate(ddate, calendars.shamsi);
    gregorian = DayToDate(ddate, calendars.gregorian);
}
