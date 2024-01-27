#define FORMATTED_OUTPUT
#include "cli.hpp"

int UserOptionInput(std::string prompt_text, std::string error_text, std::string options_list[], int options_number, int *argument)
{
    std::string user_input;
    bool first_error = true;

    while (true)
    {
        std::cout << prompt_text;
        getline(std::cin, user_input);

        for (int i = 0; i < options_number; i++)
        {
            long unsigned int lenght = options_list[i].length();
            if (options_list[i][lenght - 1] == ' ')
            {
                int equal = true;
                for (unsigned long int ii = 0; ii < lenght; ii++)
                {
                    if (options_list[i][ii] != tolower(user_input[ii]))
                    {
                        equal = false;
                        break;
                    }
                }
                if (equal)
                {
                    *argument = atoi(&user_input[lenght]);
                    if (*argument == 0)
                        continue;
                    return i;
                }
            }
            else
            {
                if (user_input.length() != lenght)
                    continue;
                int equal = true;
                for (unsigned long int ii = 0; ii < lenght; ii++)
                {
                    if (options_list[i][ii] != tolower(user_input[ii]))
                    {
                        equal = false;
                        break;
                    }
                }
                if (equal)
                {
                    return i;
                }
            }
        }

        if (first_error)
        {
            std::cout << BACKLINE;
            first_error = false;
        }
        else
        {
            std::cout << BACKLINE << BACKLINE;
        }

        std::cout << error_text << std::endl;
    }
}

std::string UserStringInput(std::string prompt_text, bool multi_line, std::string error_text)
{
    std::string user_input;
    std::cout << prompt_text;
    getline(std::cin, user_input);

    if (multi_line)
    {
        std::string return_text;
        bool first_time = true;
        while (user_input.length() != 0)
        {
            if (first_time)
                first_time = false;
            else
                return_text += '\n';
            return_text.append(user_input);
            getline(std::cin, user_input);
        }
        return return_text;
    }
    else
    {
        bool first_error = false;
        unsigned long int lenght = user_input.length();
        while (true)
        {
            lenght = user_input.length();
            for (int i = lenght - 1; i >= 0; i--)
            {
                if (isblank(user_input[i]))
                    lenght--;
            }
            if (lenght)
                return user_input;

            if (first_error)
            {
                std::cout << BACKLINE;
                first_error = false;
            }
            else
            {
                std::cout << BACKLINE << BACKLINE;
            }
            std::cout << error_text << std::endl
                      << prompt_text;
            getline(std::cin, user_input);
        }
    }
}

_date UserDateInput(std::string prompt_text, std::string error_text, _calendar calendar)
{
    _date date;

    std::string user_input;
    bool first_error = true;

    while (true)
    {
        std::cout << prompt_text;
        getline(std::cin, user_input);
        // YYYY/MM/DD
        if (user_input.length() >= 8 && user_input.length() <= 10)
        {
            date.year = atoi(user_input.c_str());
            date.month = atoi(user_input.c_str() + 5);
            if (!isdigit(user_input[6]))
                date.day = atoi(user_input.c_str() + 7);
            else
                date.day = atoi(user_input.c_str() + 8);

            if (date.IsVaild(calendar))
                return date;
        }

        if (first_error)
        {
            std::cout << BACKLINE;
            first_error = false;
        }
        else
        {
            std::cout << BACKLINE << BACKLINE;
        }

        std::cout << error_text << std::endl;
    }
}

void Header()
{
    std::cout << BOLD << "\t\t\tCalendar " << VERSION << RESET << std::endl;
    Line();
}
void Line()
{
    std::cout << GREEN;
    for (int i = 0; i < WIDTH; i++)
        std::cout << "*";
    std::cout << RESET << std::endl;
}