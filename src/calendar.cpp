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
int Event_Edit_Page(_event *);
int Task_Edit_Page(_event *);
int More_Options_Page();
int Event_Search_String_Page(std::string);
int Task_Search_String_Page(std::string);

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

    std::cout << BOLD << ">Events<" << RESET << std::endl;

    int today_events[EVENT_LIST_SIZE];
    int today_events_size;
    today_events_size = events.EventsOccurOnDate(selected_day.shamsi, today_events, *default_calendar);

    for (int i = 0; i < today_events_size; i++)
    {
        std::cout << i + 1 << "- " << events.event_ptr[today_events[i]]->title << std::endl;
    }

    std::cout << std::endl;
    std::cout << BOLD << ">Tasks<" << RESET << std::endl;

    int today_tasks[EVENT_LIST_SIZE];
    int today_tasks_size;
    today_tasks_size = events.TasksOccurOnDate(selected_day.shamsi, today_tasks, *default_calendar);

    for (int i = 0; i < today_tasks_size; i++)
    {
        std::cout << i + 1 << "- " << events.event_ptr[today_tasks[i]]->title;
        if (events.event_ptr[today_tasks[i]]->IsTaskDone())
        {
            std::cout << " **DONE**";
        }
        NLINE;
    }
    NLINE;

    Line();

    std::cout << BOLD << message << std::endl
              << "Write a command and press \"Enter\"" << RESET << std::endl;

    std::cout << "N:\tNext Day" << std::endl
              << "P:\tPrevious day" << std::endl
              << "NE:\tNew Event" << std::endl
              << "NT:\tNew Task" << std::endl
              << "DE n:\tDelete #n Event" << std::endl
              << "DT n:\tDetete #n Task" << std::endl
              << "TT n:\tToggle Status Of #n Task" << std::endl
              << "EE n:\tEdit #n Event" << std::endl
              << "ET n:\tEdit #n Task" << std::endl
              //<< "GD: Goto Date" << std::endl
              << "M:\tMore Options" << std::endl
              << "Q:\tQuit" << std::endl
              << std::endl;

    std::string options[] = {"n", "p", "ne", "nt", "de ", "dt ", "tt ", "ee ", "et ", "m", "q"};
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
            message = "Out of range!";
            break;
        }
        events.Remove(today_events[argument - 1]);
        events.EventListSaveToFile();
        message = "";
        break;
    case 5:
        if (argument < 1 || argument > today_tasks_size)
        {
            message = "Out of range!";
            break;
        }
        events.Remove(today_tasks[argument - 1]);
        events.EventListSaveToFile();
        message = "";
        break;
    case 6:
        if (argument < 1 || argument > today_tasks_size)
        {
            message = "Out of range!";
            break;
        }
        events.event_ptr[today_tasks[argument - 1]]->ToggleDone();
        events.EventListSaveToFile();
        message = "";
        break;
    case 7:
        if (argument > today_events_size)
        {
            message = "Out of range!";
            break;
        }
        switch (Event_Edit_Page(events.event_ptr[today_events[argument - 1]]))
        {
        case 0:
            break;
        case 1:
            events.Sort();
            events.EventListSaveToFile();
            message = "";
            break;
        case 2:
            events.Remove(today_events[argument - 1]);
            events.EventListSaveToFile();
            message = "";
            break;
        default:
            message = "UNKNOWN ERROR!";
            break;
        }
        break;
    case 8:
        if (argument > today_tasks_size)
        {
            message = "Out of range!";
            break;
        }
        switch (Task_Edit_Page(events.event_ptr[today_tasks[argument - 1]]))
        {
        case 0:
            break;
        case 1:
            events.Sort();
            events.EventListSaveToFile();
            message = "";
            break;
        case 2:
            events.Remove(today_tasks[argument - 1]);
            events.EventListSaveToFile();
            message = "";
            break;
        default:
            message = "UNKNOWN ERROR!";
            break;
        }
        break;
    case 9:
        while (More_Options_Page())
        {
        }
        message = "";
        break;
    case 10:
        message = "";
        return 0;
        break;
    default:
        message = "UNKNOWN ERROR!";
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
    new_event.description = UserStringInput("Description (enter an empty line to end text): ");

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
    new_task.description = UserStringInput("Description (enter an empty line to end text): ");

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

int Event_Edit_Page(_event *event)
{
    int edited = false;
    while (true)
    {
        CLEAR;
        Header();

        std::cout << BOLD << "Title: " << RESET << event->title << std::endl
                  << BOLD << event->Status() << " " << event->Type() << ", ";
        switch (event->id)
        {
        case 0:
            std::cout << RESET << "On " << BOLD;
            break;
        case 1:
            std::cout << "Every " << event->date.day << " " << default_calendar->month_name[event->date.month] << RESET << " from ";
            break;
        case 2:
            std::cout << "Every " << event->date.day << RESET << " from ";
            break;
        case 3:
            std::cout << "Every " << default_calendar->weekday_name[Weekday(DateToDay(event->date, *default_calendar), *default_calendar)] << RESET << " from ";
            break;
        default:
            break;
        }
        std::cout << event->date.String(*default_calendar) << std::endl
                  << BOLD << "Description: " << RESET << event->description << std::endl;
        Line();
        std::cout << "ET:\tEdit Title" << std::endl
                  << "ED:\tEdit Date" << std::endl
                  << "EDE:\tEdit Description" << std::endl
                  << "ETY:\tEdit Event Type" << std::endl
                  << "D:\tDelete Event" << std::endl
                  << "B:\tGo Back" << std::endl;

        std::string options[] = {"et", "ed", "ede", "ety", "d", "b"};
        int user_input;
        user_input = UserOptionInput(COMMAND_STRING, "Incorrect command!", options, sizeof(options) / sizeof(std::string));
        std::string type_options[] = {"s", "y", "m", "w"};

        switch (user_input)
        {
        case 0:
            event->title = UserStringInput("Title: ", false, "Title can't be empty!");
            edited = true;
            break;
        case 1:
            event->date = UserDateInput("Enter a date:", "Incorrect! (date format: YYYY MM DD)", *default_calendar);
            if (event->date.year < default_calendar->origin.year)
                event->date.year = default_calendar->origin.year;
            edited = true;
            break;
        case 2:
            event->description = UserStringInput("New Description (enter an empty line to): ");
            edited = true;
            break;
        case 3:
            event->id = UserOptionInput("Event type: (S)pecific_date (Y)early (M)onthly (W)eekly: ", "Wrong Input!", type_options, sizeof(options) / sizeof(std::string));
            edited = true;
            break;
        case 4:
            return 2;
            break;
        case 5:
            return edited;
            break;
        default:
            break;
        }
    }
}

int Task_Edit_Page(_event *event)
{
    int edited = false;
    while (true)
    {
        CLEAR;
        Header();
        std::cout << BOLD << "Title: " << RESET << event->title << std::endl
                  << BOLD << "Date: " << RESET << event->date.String(*default_calendar) << std::endl
                  << BOLD << "Status: " << RESET << event->Status() << std::endl
                  << BOLD << "Description (enter an empty line to end text): " << RESET << event->description << std::endl;
        Line();
        std::cout << "ET:\tEdit Title" << std::endl
                  << "ED:\tEdit Date" << std::endl
                  << "EDE:\tEdit Description" << std::endl
                  << "T:\tToggle Status" << std::endl
                  << "D:\tDelete Task" << std::endl
                  << "B:\tGo Back" << std::endl;

        std::string options[] = {"et", "ed", "ede", "t", "d", "b"};
        int user_input;
        user_input = UserOptionInput(COMMAND_STRING, "Incorrect command!", options, sizeof(options) / sizeof(std::string));
        std::string type_options[] = {"s", "y", "m", "w"};

        switch (user_input)
        {
        case 0:
            event->title = UserStringInput("Title: ", false, "Title can't be empty!");
            edited = true;
            break;
        case 1:
            event->date = UserDateInput("Enter a date:", "Incorrect! (date format: YYYY MM DD)", *default_calendar);
            if (event->date.year < default_calendar->origin.year)
                event->date.year = default_calendar->origin.year;
            edited = true;
            break;
        case 2:
            event->description = UserStringInput("New Description(enter an empty line to): ");
            edited = true;
            break;
        case 3:
            event->ToggleDone();
            edited = true;
            break;
        case 4:
            return 2;
            break;
        case 5:
            return edited;
            break;
        default:
            break;
        }
    }
}

int More_Options_Page()
{

    static std::string message;
    int user_input;

    CLEAR;
    Header();

    std::cout << calendars.shamsi.name << ":    " << selected_day.shamsi.year << "/" << selected_day.shamsi.month << "/" << selected_day.shamsi.day << "\t" << calendars.shamsi.weekday_name[Weekday(selected_day.ddate, calendars.shamsi)] << std::endl;
    std::cout << calendars.gregorian.name << ": " << selected_day.gregorian.year << "-" << selected_day.gregorian.month << "-" << selected_day.gregorian.day << "\t" << calendars.gregorian.weekday_name[Weekday(selected_day.ddate, calendars.gregorian)] << std::endl;

    Line();

    std::cout << message << std::endl
              << "GD:\tGoto Date" << std::endl
              << "UE:\tUpcoming Events" << std::endl
              << "UT:\tUpcoming Tasks" << std::endl
              << "LT:\tShow Late Tasks" << std::endl
              << "SE:\tSearch In Events" << std::endl
              << "ST:\tSearch In Tasks" << std::endl
              << "B:\tBack To Homepage" << std::endl
              << std::endl;

    std::string options[] = {"gd", "ue", "ut", "lt", "se", "st", "b"};
    user_input = UserOptionInput(COMMAND_STRING, "Incorrect command!", options, sizeof(options) / sizeof(std::string));
    std::string search_string;
    switch (user_input)
    {
    case 0:
        *default_selected_date = UserDateInput("Enter a date:", "Incorrect! (date format: YYYY MM DD)", *default_calendar);
        selected_day.ddate = DateToDay(*default_selected_date, *default_calendar);
        selected_day.RegenerateDates();
        break;
    case 4:
        search_string = UserStringInput("string to search:", false, "error!");
        while (Event_Search_String_Page(search_string))
        {
        }
        break;
    case 5:
        search_string = UserStringInput("string to search:", false, "error!");
        while (Task_Search_String_Page(search_string))
        {
        }
        break;
    case 6:
        return 0;
        break;
    default:
        message = "UNKNOWN ERROR!";
        break;
    }

    return 1;
}

int Event_Search_String_Page(std::string search_string)
{
    std::string message;
    int edited = false;
    int result[events.real_size], result_size;
    result_size = events.EventSearchByString(search_string, result);
    while (true)
    {
        CLEAR;
        Header();
        if (result_size == 0)
        {
            std::cout << "No Result!" << std::endl
                      << "Press enter to continue" << std::endl;
            getline(std::cin, message);
            return 0;
        }

        for (int i = 0; i < result_size; i++)
        {
            _event *event = events.event_ptr[result[i]];
            std::cout << i + 1 << "- " << event->title << ", " << BOLD << event->Status() << ", ";
            switch (event->id)
            {
            case 0:
                std::cout << RESET << "On " << BOLD;
                break;
            case 1:
                std::cout << "Every " << event->date.day << " " << default_calendar->month_name[event->date.month] << RESET << " from ";
                break;
            case 2:
                std::cout << "Every " << event->date.day << RESET << " from ";
                break;
            case 3:
                std::cout << "Every " << default_calendar->weekday_name[Weekday(DateToDay(event->date, *default_calendar), *default_calendar)] << RESET << " from ";
                break;
            default:
                break;
            };
            std::cout << event->date.String(*default_calendar) << RESET << std::endl;
        }
        Line();

        std::cout << message << std::endl
                  << "E n:\tEdit #n Event" << std::endl
                  << "D n:\tDelete #n Event" << std::endl
                  << "B:\tBack to HomePage" << std::endl
                  << std::endl;

        std::string options[] = {"e ", "d ", "b"};
        int argument, user_input;
        user_input = UserOptionInput(COMMAND_STRING, "Incorrect command!", options, sizeof(options) / sizeof(std::string), &argument);
        switch (user_input)
        {
        case 0:
            if (argument > result_size)
            {
                message = "Out of range!";
                break;
            }
            switch (Event_Edit_Page(events.event_ptr[result[argument - 1]]))
            {
            case 0:
                break;
            case 1:
                edited = true;
                events.Sort();
                events.EventListSaveToFile();
                message = "";
                break;
            case 2:
                edited = true;
                events.Remove(result[argument - 1]);
                events.EventListSaveToFile();
                message = "";
                break;
            default:
                message = "UNKNOWN ERROR!";
                break;
            }
            break;
        case 1:
            if (argument > result_size)
            {
                message = "Out of range!";
                break;
            }
            edited = true;
            events.Remove(result[argument - 1]);
            events.EventListSaveToFile();
            message = "";
            break;
        case 2:
            message = "";
            return 0;
            break;
        default:
            break;
        }
        if (edited)
            break;
    }
    return 1;
}

int Task_Search_String_Page(std::string search_string)
{
    std::string message;
    int edited = false;
    int result[events.real_size], result_size;
    result_size = events.TaskSearchByString(search_string, result);
    while (true)
    {
        CLEAR;
        Header();
        if (result_size == 0)
        {
            std::cout << "No Result!" << std::endl
                      << "Press enter to continue" << std::endl;
            getline(std::cin, message);
            return 0;
        }

        for (int i = 0; i < result_size; i++)
        {
            _event *event = events.event_ptr[result[i]];
            std::cout << i + 1 << "- " << event->title << ", " << BOLD << event->Status() << ", " << event->date.String(*default_calendar) << RESET << std::endl;
        }
        Line();

        std::cout << message << std::endl
                  << "E n:\tEdit #n Task" << std::endl
                  << "D n:\tDelete #n Task" << std::endl
                  << "B:\tBack to HomePage" << std::endl
                  << std::endl;

        std::string options[] = {"e ", "d ", "b"};
        int argument, user_input;
        user_input = UserOptionInput(COMMAND_STRING, "Incorrect command!", options, sizeof(options) / sizeof(std::string), &argument);
        switch (user_input)
        {
        case 0:
            if (argument > result_size)
            {
                message = "Out of range!";
                break;
            }
            switch (Event_Edit_Page(events.event_ptr[result[argument - 1]]))
            {
            case 0:
                break;
            case 1:
                edited = true;
                events.Sort();
                events.EventListSaveToFile();
                message = "";
                break;
            case 2:
                edited = true;
                events.Remove(result[argument - 1]);
                events.EventListSaveToFile();
                message = "";
                break;
            default:
                message = "UNKNOWN ERROR!";
                break;
            }
            break;
        case 1:
            if (argument > result_size)
            {
                message = "Out of range!";
                break;
            }
            edited = true;
            events.Remove(result[argument - 1]);
            events.EventListSaveToFile();
            message = "";
            break;
        case 2:
            message = "";
            return 0;
            break;
        default:
            break;
        }
        if (edited)
            break;
    }
    return 1;
}
