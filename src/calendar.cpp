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

int Start_Page(int *);
int Event_Add_Page();
void Header();
int Event_Search_String(std::string);
void Line();

int main()
{
    events.EventListLoadFromFile(*default_calendar);
    today.ddate = SystemDDate();
    today.RegenerateDates();
    selected_day = today;
    int controller, argument;
    std::string search_string;
    while (true)
    {
        controller = Start_Page(&argument);
        switch (controller)
        {
        case 0:
            selected_day.ddate += 1;
            selected_day.RegenerateDates();
            break;
        case 1:
            if (selected_day.ddate > 0)
            {
                selected_day.ddate -= 1;
                selected_day.RegenerateDates();
            }
            break;
        case 2:
            return 0;
            break;
        case 3:
            Event_Add_Page();
            break;
        case 4:
            events.Remove(today_events[argument - 1]);
            events.EventListSaveToFile();
            break;
        case 5:
            *default_selected_date = UserDateInput("Enter a date:", "haha!", *default_calendar);
            selected_day.ddate = DateToDay(*default_selected_date, *default_calendar);
            selected_day.RegenerateDates();
            break;
        case 6:
            search_string = UserStringInput("string to search:", false, "error!");
            Event_Search_String(search_string);
            break;
        default:
            break;
        }
    }
}

int Start_Page(int *argument)
{
    int user_input;

    CLEAR;
    Header();

    std::cout << calendars.shamsi.name << ":    " << selected_day.shamsi.year << "/" << selected_day.shamsi.month << "/" << selected_day.shamsi.day << "\t" << calendars.shamsi.weekday_name[Weekday(selected_day.ddate, calendars.shamsi)] << std::endl;
    std::cout << calendars.gregorian.name << ": " << selected_day.gregorian.year << "-" << selected_day.gregorian.month << "-" << selected_day.gregorian.day << "\t" << calendars.gregorian.weekday_name[Weekday(selected_day.ddate, calendars.gregorian)] << std::endl;

    Line();

    BOLD;
    std::cout << ">Events<";
    NLINE RESET;

    today_events_size = events.OccurOnDate(selected_day.shamsi, today_events, *default_calendar);
    for (int i = 0; i < today_events_size; i++)
    {
        std::cout << i + 1 << "- " << events.event_ptr[today_events[i]]->title << std::endl;
    }

    Line();

    BOLD;
    std::cout << "Write a command and press \"Enter\"" << std::endl;
    RESET;
    std::cout << "N: Next Day" << std::endl
              << "P: Previous day" << std::endl
              << "NE: New Event" << std::endl
              << "RE n: Remove #n Event" << std::endl
              << "SE n: Show #n Event" << std::endl
              << "GD: Goto Date" << std::endl
              << "Q: Quit" << std::endl;
    NLINE;

    std::string options[] = {"n", "p", "q", "ne", "re ", "gd", "se"};
    user_input = UserOptionInput(COMMAND_STRING, "Incorrect command!", options, 7, argument);

    return user_input;
}

int Event_Add_Page()
{
    _event new_event;
    new_event.date = *default_selected_date;
    std::string options[] = {"s", "y", "m", "w"};

    new_event.id = UserOptionInput("Event type: (S)pecific_date (Y)early (M)onthly (W)eekly: ", "Wrong Input!", options, 4);
    new_event.title = UserStringInput("Title: ", false, "Title can't be empty!");
    new_event.description = UserStringInput("Description: ");

    events.Add(new_event, *default_calendar);
    events.EventListSaveToFile();
    return 0;
}

void Header()
{
    BOLD;
    std::cout << "\t\t\tCalendar V0.4" << std::endl;
    RESET;
    Line();
}
void Line()
{
    GREEN;
    for (int i = 0; i < WIDTH; i++)
        std::cout << "*";
    NLINE RESET;
}
void _day::RegenerateDates()
{
    if (ddate < 0)
        ddate = 0;
    shamsi = DayToDate(ddate, calendars.shamsi);
    gregorian = DayToDate(ddate, calendars.gregorian);
}

int Event_Search_String(std::string search_string)
{
    CLEAR;
    int result[events.real_size], result_size = 0;
    for (int i = 0; i < events.size; i++)
    {
        if (IsInString(events.event_ptr[i]->title, search_string))
        {
            result[result_size] = i;
            result_size++;
        }
    }
    Header();
    for (int i = 0; i < result_size; i++)
    {
        std::cout << i + 1 << "- " << events.event_ptr[result[i]]->title << std::endl;
    }
    getchar();
    return 0;
}
