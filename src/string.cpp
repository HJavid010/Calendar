#include "string.hpp"

std::string StandardToRegex(std::string text)
{
    std::string output_text;
    int i = 0;
    while (text[i])
    {
        switch (text[i])
        {
        case '\"':
        case '\\':
        case '/':
            output_text.append("\\");
            output_text += text[i];
            break;
        case '\n':
            output_text.append("\\n");
            break;
        case '\t':
            output_text.append("\\t");
            break;
        default:
            output_text += text[i];
            break;
        }
        i++;
    }
    return output_text;
}

int IsInString(std::string big_string, std::string small_string)
{
    int big_string_size = big_string.length();
    int small_string_size = small_string.length();
    int found;
    for (int i = 0; i < big_string_size - small_string_size + 1; i++)
    {
        found = true;
        for (int ii = 0; ii < small_string_size; ii++)
        {
            if (tolower(big_string[i + ii]) != tolower(small_string[ii]))
            {
                found = false;
                break;
            }
        }
        if (found)
            break;
    }
    return found;
}

int LineToStringList(std::string text, std::string out_text[], int out_size)
{
    int array_size = 0;
    int i = 0;
    int found = false;
    while (text[i] != 0)
    {
        if (found)
        {
            if (text[i] != ',')
                return -1;
            else
                i++;
        }
        while (isblank(text[i]))
        {
            i++;
        }
        if (text[i] == '\"')
        {
            found = true;
            i++;
            out_text[array_size] += '\"';
            while (text[i] != '\"')
            {
                if (text[i] == '\\')
                {
                    i++;
                    switch (text[i])
                    {
                    case 0:
                        return -1;
                    case '\"':
                        out_text[array_size] += '\"';
                        break;
                    case '\\':
                        out_text[array_size] += '\\';
                        break;
                    case '/':
                        out_text[array_size] += '/';
                        break;
                    case 'n':
                        out_text[array_size] += '\n';
                        break;
                    case 't':
                        out_text[array_size] += '\t';
                        break;
                    default:
                        out_text[array_size] += '\\';
                        break;
                    }
                }
                else
                    out_text[array_size] += text[i];
                i++;
            }
            out_text[array_size] += text[i];
            i++;
            array_size++;
        }
        else if (isdigit(text[i]))
        {
            found = true;
            while (isdigit(text[i]))
            {
                out_text[array_size] += text[i];
                i++;
            }
            array_size++;
        }
        while (isblank(text[i]))
        {
            i++;
        }
        if (array_size == out_size)
            return array_size;
    }
    return array_size;
}

std::string RemoveQuotation(std::string text)
{
    std::string out_text;
    int text_size = text.length();
    for (int i = 1; i < text_size - 1; i++)
        out_text += text[i];
    return out_text;
}