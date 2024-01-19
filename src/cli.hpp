#ifndef CLI_H
#define CLI_H 1

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

#define BOLD std::cout << "\033[1m";
#define GREEN std::cout << "\033[32m";
#define RED std::cout << "\033[31m";
#define RESET std::cout << "\033[0m";
#define NLINE std::cout << std::endl;
#define WIDTH 61

#endif /* CLI_H */