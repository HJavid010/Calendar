#ifndef STRING_H
#define STRING_H 1

#include <iostream>

std::string StandardToRegex(std::string);
int IsInString(std::string, std::string);
int LineToStringList(std::string text, std::string out_text[],int size);
std::string RemoveQuotation(std::string);

#endif