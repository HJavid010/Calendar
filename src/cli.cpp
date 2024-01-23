#define FORMATTED_OUTPUT
#include "cli.hpp"

int UserInput(std::string prompt_text, std::string error_text, std::string options_list[], int options_number, int *argument)
{
    std::string user_input;
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

    BACKLINE;
    while (true)
    {

        std::cout << error_text << std::endl
                  << prompt_text;

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
        BACKLINE BACKLINE;
    }
}