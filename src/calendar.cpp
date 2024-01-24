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
int Event_Add();
int Task_Add();

int Event_Search_String_Page(std::string);

int main()
{
    events.EventListLoadFromFile(*default_calendar);
    today.ddate = SystemDDate();
    today.RegenerateDates();
    selected_day = today;
    while (Start_Page())
    {
    }
    return 0;
}

int Start_Page()
{
    static std::string message;
    int user_input;

    CLEAR;
    Header();

    std::cout << calendars.shamsi.name << ":    " << selected_day.shamsi.year << "/" << selected_day.shamsi.month << "/" << selected_day.shamsi.day << "\t" << calendars.shamsi.weekday_name[Weekday(selected_day.ddate, calendars.shamsi)] << std::endl;
    std::cout << calendars.gregorian.name << ": " << selected_day.gregorian.year << "-" << selected_day.gregorian.month << "-" << selected_day.gregorian.day << "\t" << calendars.gregorian.weekday_name[Weekday(selected_day.ddate, calendars.gregorian)] << std::endl;

    Line();

    BOLD;
    std::cout << ">Events<";
    NLINE RESET;

    int today_events[EVENT_LIST_SIZE];
    int today_events_size;
    today_events_size = events.EventsOccurOnDate(selected_day.shamsi, today_events, *default_calendar);

    for (int i = 0; i < today_events_size; i++)
    {
        std::cout << i + 1 << "- " << events.event_ptr[today_events[i]]->title << std::endl;
    }

    NLINE BOLD;
    std::cout << ">Tasks<" << std::endl;
    RESET;

    int today_tasks[EVENT_LIST_SIZE];
    int today_tasks_size;
    today_tasks_size = events.TasksOccurOnDate(selected_day.shamsi, today_tasks, *default_calendar);

    for (int i = 0; i < today_tasks_size; i++)
    {
        std::cout << i + 1 << "- " << events.event_ptr[today_tasks[i]]->title;
        if (events.event_ptr[today_tasks[i]]->id == 5)
        {
            std::cout << " **DONE**";
        }
        NLINE;
    }
    NLINE;

    Line();

    BOLD;
    std::cout << message << std::endl
              << "Write a command and press \"Enter\"" << std::endl;
    RESET;
    std::cout << "N:\tNext Day" << std::endl
              << "P:\tPrevious day" << std::endl
              << "NE:\tNew Event" << std::endl
              << "NT:\tNew Task" << std::endl
              << "RE n:\tRemove #n Event" << std::endl
              << "RT n:\tRemove #n Task" << std::endl
              << "EE n:\tEdit #n Event" << std::endl
              << "ET n:\tEdit #n Task" << std::endl
              //<< "GD: Goto Date" << std::endl
              << "M:\tMore options" << std::endl
              << "Q:\tQuit" << std::endl;
    NLINE;

    std::string options[] = {"n", "p", "ne", "nt", "re ", "rt ", "ee ", "et ", "m", "q"};
    int argument;
    user_input = UserOptionInput(COMMAND_STRING, "Incorrect command!", options, sizeof(options) / sizeof(std::string), &argument);

    std::string search_string;
    switch (user_input)
    {
    case 0:
        selected_day.ddate += 1;
        selected_day.RegenerateDates();
        message = "";
        break;
    case 1:
        if (selected_day.ddate > 0)
        {
            selected_day.ddate -= 1;
            selected_day.RegenerateDates();
            message = "";
        }
        else
            message = "can't go back!";
        break;

    case 2:
        Event_Add();
        message = "";
        break;
    case 3:
        Task_Add();
        message = "";
        break;
    case 4:
        if (argument > today_events_size)
        {
            message = "out of range!";
            break;
        }
        events.Remove(today_events[argument - 1]);
        events.EventListSaveToFile();
        break;
    case 5:
        if (argument < 1 || argument > today_tasks_size + 1)
        {
            message = "out of range!";
            break;
        }
        events.Remove(today_tasks[argument - 1]);
        events.EventListSaveToFile();
        break;
    /*case 5:
        *default_selected_date = UserDateInput("Enter a date:", "haha!", *default_calendar);
        selected_day.ddate = DateToDay(*default_selected_date, *default_calendar);
        selected_day.RegenerateDates();
        break;
    case 6:
        search_string = UserStringInput("string to search:", false, "error!");
        Event_Search_String_Page(search_string);
        break;*/
    case 9:
        return 0;
        break;
    default:
        break;
    }

    return 1;
}

int Event_Add()
{
    _event new_event;
    new_event.date = *default_selected_date;
    std::string options[] = {"s", "y", "m", "w"};

    new_event.id = UserOptionInput("Event type: (S)pecific_date (Y)early (M)onthly (W)eekly: ", "Wrong Input!", options, sizeof(options) / sizeof(std::string));
    new_event.title = UserStringInput("Title: ", false, "Title can't be empty!");
    new_event.description = UserStringInput("Description: ");

    events.Add(new_event, *default_calendar);
    events.EventListSaveToFile();
    return 0;
}

int Task_Add()
{
    _event new_task;
    new_task.date = *default_selected_date;

    new_task.id = 4;
    new_task.title = UserStringInput("Title: ", false, "Title can't be empty!");
    new_task.description = UserStringInput("Description: ");

    events.Add(new_task, *default_calendar);
    events.EventListSaveToFile();
    return 0;
}

void _day::RegenerateDates()
{
    if (ddate < 0)
        ddate = 0;
    shamsi = DayToDate(ddate, calendars.shamsi);
    gregorian = DayToDate(ddate, calendars.gregorian);
}

int Event_Search_String_Page(std::string search_string)
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
