#ifndef CLI_H
#define CLI_H 1

#include <iostream>
#include "date.hpp"

#if defined _WIN32
#define CLEAR system("cls");
// clrscr(); // including header file : conio.h
#elif defined(__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
#define CLEAR system("clear");
// std::cout<< u8"\x1b[2J\x1b[1;1H"; //Using ANSI Escape Sequences
#elif defined(__APPLE__)
#define CLEAR system("clear");
#endif // defined _WIN32

#define NLINE std::cout << std::endl;
#define WIDTH 61

#ifndef FORMATTED_OUTPUT_DEFINED
#define FORMATTED_OUTPUT_DEFINED 1
#ifdef FORMATTED_OUTPUT

#define BOLD std::cout << "\x1b[1m";
#define GREEN std::cout << "\x1b[32m";
#define RED std::cout << "\x1b[31m";
#define RESET std::cout << "\x1b[0m";
#define BACKLINE std::cout << "\x1b[1F\x1b[2K";
#define COMMAND_STRING "\x1b[1;31m>>> \x1b[0m"

#else

#define BOLD
#define GREEN
#define RED
#define RESET
#define BACKLINE
#define COMMAND_STRING ">>> "

#endif /* FORMATTED_OUTPUT */

#endif /* FORMATTED_OUTPUT_DEFINED */

int UserOptionInput(std::string, std::string, std::string[], int, int *arguman = 0);
std::string UserStringInput(std::string, bool multi_line = true, std::string error_text = "");
_date UserDateInput(std::string, std::string, _calendar);

#endif /* CLI_H */