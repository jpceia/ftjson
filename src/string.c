#include "ftjson.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Creates json from string
t_json json_from_string(char *string)
{
    t_json json;

    json.type = JSON_STRING;
    json.string = strdup(string);
    return json;
}

// Converts a json string to string, with quotes
char *json_string_stringify(char *string)
{
    char *text;

    text = malloc(strlen(string) + 3);
    if (text == NULL)
        return NULL;
    strcpy(text, "\"");
    strcat(text, string);
    strcat(text, "\"");
    return text;
}

// Converts 4 hex to a utf-8 char
void hex_to_utf8(char *hex, char *utf8)
{
    *utf8 = hex[0] - '0';
    *utf8 = (*utf8 << 4) + (hex[1] - '0');
    *utf8 = (*utf8 << 4) + (hex[2] - '0');
    *utf8 = (*utf8 << 4) + (hex[3] - '0');
}

// Parse a Json string from a string
char *json_string_parse(char **str)
{
    char *text = NULL;
    int i = 0;
    int size = 8; // initial size

    if (**str != '"')
        return NULL;
    text = malloc(size + 1);
    ++*str;
    while (**str != '"' && **str != '\0')
    {
        if (**str == '\n' || **str == '\r' || **str == '\t' || **str == '\b' || **str == '\f')
        {
            perror("Control character in string");
            free(text);
            return NULL;
        }
        if (i + 1 >= size)
        {
            size *= 2;
            if (realloc(text, size + 1) == NULL)
            {
                perror("Realloc failed");
                free(text);
                return NULL;
            }
        }
        if (**str == '\\')
        {
            ++*str;
            switch (**str)
            {
            case '"':
                text[i++] = '"';
                break;
            case '\\':
                text[i++] = '\\';
                break;
            case '/':
                text[i++] = '/';
                break;
            case 'b':
                text[i++] = '\b';
                break;
            case 'f':
                text[i++] = '\f';
                break;
            case 'n':
                text[i++] = '\n';
                break;
            case 'r':
                text[i++] = '\r';
                break;
            case 't':
                text[i++] = '\t';
                break;
            case 'u':
                ++*str;
                hex_to_utf8(*str, &text[i++]);
                *str += 3;
                break;
            default:
                perror("Invalid escape sequence");
                return NULL; // Invalid escape sequence
            }
        }
        else
            text[i++] = **str;
        ++*str;
    }
    if (**str != '"')
    {
        perror("Unterminated string");
        free(text);
        return NULL;
    }
    if (i < size)
    {
        if (realloc(text, i + 1) == NULL)
        {
            perror("Realloc failed");
            free(text);
            return NULL;
        }
    }
    ++*str;
    text[i] = '\0';
    return text;
}
