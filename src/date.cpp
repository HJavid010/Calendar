#include "date.hpp"

struct _calendars
{
    struct _shamsi
    {
        unsigned int id = 0;
        _date origin{.year = 1348, .month = 10, .day = 11};
        std::string months[12] = {"Farvardin", "Ordibehesht", "Khordad", "Tir", "Mordad", "Shahrivar", "Mehr", "Aban", "Azar", "Dey", "Bahman", "Esfand"};
        int IsLeapYear(int year);
    } shamsi;

    struct _georgian
    {
        unsigned int id = 1;
        _date origin{.year = 1970, .month = 1, .day = 1};
        std::string months[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
        int IsLeapYear(int year);
    } georgian;

    struct _ghamari
    {
        unsigned int id = 2;
        _date origin{.year = 1389, .month = 10, .day = 22};
        std::string months[12] = {"al-Muharram", "Safar", "Rabi`al-Awwal", "Rabi`al-Thani", "Jumada`al-Ula", "Jumada`al-Thani", "Rajab", "Sha`ban", "Ramadan", "Shawwal", "Dhu`al-Qadah", "Dhu`al-Hijjah"};
        int IsLeapYear(int year);
    } ghamari;

} calendars;
