#include "string.hpp"
#include "date.hpp"
#include "event.hpp"
#define FORMATTED_OUTPUT
#include "cli.hpp"

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

int today_events[EVENT_LIST_SIZE];
int today_events_size;

_calendar *default_calendar = &calendars.shamsi;
_event_list events;

struct _day
{
    int ddate;
    _date shamsi;
    _date gregorian;
    void RegenerateDates();
} selected_day, today;

_date *default_selected_date = &selected_day.shamsi, *default_toda_date = &today.shamsi;

int Start_Page();
int Event_Add_Page();
int Event_Remove_Page();
int Help_Menu();
int main()
{
    events.EventListLoadFromFile(*default_calendar);
    today.ddate = SystemDDate();
    today.RegenerateDates();
    selected_day = today;
    int controller;
    while (true)
    {
        controller = Start_Page();
        switch (controller)
        {
        case 1:
            selected_day.ddate += 1;
            selected_day.RegenerateDates();
            break;
        case 2:
            if (selected_day.ddate > 0)
            {
                selected_day.ddate -= 1;
                selected_day.RegenerateDates();
            }
            break;
        case 3:
            return 0;
            break;
        case 4:
            Event_Add_Page();
            break;
        case 5:
            Event_Remove_Page();
            break;
        default:
            break;
        }
    }
}

int Start_Page()
{
    std::string user_input;

    CLEAR BOLD;
    std::cout << "\t\t\tCalendar V1.2" << std::endl;
    RESET GREEN;
    for (int i = 0; i < WIDTH; i++)
        std::cout << "*";
    NLINE RESET;
    std::cout << calendars.shamsi.name << ":    " << selected_day.shamsi.year << "/" << selected_day.shamsi.month << "/" << selected_day.shamsi.day << "\t" << calendars.shamsi.weekday_name[Weekday(selected_day.ddate, calendars.shamsi)] << std::endl;
    std::cout << calendars.gregorian.name << ": " << selected_day.gregorian.year << "-" << selected_day.gregorian.month << "-" << selected_day.gregorian.day << "\t" << calendars.gregorian.weekday_name[Weekday(selected_day.ddate, calendars.gregorian)] << std::endl;
    GREEN;
    for (int i = 0; i < 61; i++)
        std::cout << "*";
    NLINE RESET;

    BOLD;
    std::cout << ">Events<" << std::endl;
    RESET;

    today_events_size = events.SearchByDate(selected_day.shamsi, today_events, *default_calendar);
    for (int i = 0; i < today_events_size; i++)
    {
        std::cout << i + 1 << "- " << events.event_ptr[today_events[i]]->title << std::endl;
    }
    NLINE;
    GREEN
    for (int i = 0; i < 61; i++)
        std::cout << "*";
    RESET
    NLINE;
    Help_Menu();
    NLINE;

    BOLD RED;
    std::cout << ">>> ";
    RESET

    getline(std::cin, user_input);
    if (user_input == "N")
        return 1;
    if (user_input == "P")
        return 2;
    if (user_input == "Q")
        return 3;
    if (user_input == "NE")
        return 4;
    if (user_input == "RE")
        return 5;
    return 0;
}

int Event_Add_Page()
{
    _event new_event;
    new_event.date = *default_selected_date;
    std::string event_type;

    std::cout << "Event type: (s)pecific date (y)early (m)onthly (w)eekly" << std::endl;
    getline(std::cin, event_type);

    int vaild_input = true;

    if (event_type == "s")
        new_event.id = 0;
    else if (event_type == "y")
        new_event.id = 1;
    else if (event_type == "m")
        new_event.id = 2;
    else if (event_type == "w")
        new_event.id = 3;
    else
    {
        vaild_input = false;
        while (!vaild_input)
        {
            getline(std::cin, event_type);

            vaild_input = true;

            if (event_type == "s")
                new_event.id = 0;
            else if (event_type == "y")
                new_event.id = 1;
            else if (event_type == "m")
                new_event.id = 2;
            else if (event_type == "w")
                new_event.id = 3;
            else
            {
                std::cout << event_type;
                vaild_input = false;
            }
        }
    }

    std::cout << "Title: ";
    getline(std::cin, new_event.title);
    if (new_event.title.length() == 0)
    {
        vaild_input = false;
        while (!vaild_input)
        {
            vaild_input = true;
            getline(std::cin, new_event.title);
            if (new_event.title.length() == 0)
                vaild_input = false;
        }
    }

    std::cout << "Description: ";
    getline(std::cin, new_event.description);

    events.Add(new_event, *default_calendar);
    events.EventListSaveToFile();
    return 0;
}

int Event_Remove_Page()
{
    int index;
    std::cout << "Wich Event do you want to remove:" << std::endl;
    std::cin >> index;
    events.Remove(today_events[index - 1]);
    events.EventListSaveToFile();

    return 0;
}

void _day::RegenerateDates()
{
    shamsi = DayToDate(ddate, calendars.shamsi);
    gregorian = DayToDate(ddate, calendars.gregorian);
}

int Help_Menu()
{
    std::cout << "Write a command and press ";
    NLINE;
    std::cout << "N: Next Day";
    NLINE;
    std::cout << "P: Previous day";
    NLINE;
    std::cout << "NE: New Event";
    NLINE;
    std::cout << "RE: Remove Event";
    NLINE;
    std::cout << "ED: Event dicription";
    NLINE;
    std::cout << "Q: Quit";
    NLINE;
    return 0;
}
