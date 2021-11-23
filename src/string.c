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
    text[0] = '\0';
    strcat(text, "\"");
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

char json_control_character_parse(char **str)
{
    char c;

    switch (**str)
    {
    case '"':
        c = '"';
        break;
    case '\\':
        c = '\\';
        break;
    case '/':
        c = '/';
        break;
    case 'b':
        c = '\b';
        break;
    case 'f':
        c = '\f';
        break;
    case 'n':
        c = '\n';
        break;
    case 'r':
        c = '\r';
        break;
    case 't':
        c = '\t';
        break;
    case 'u':
        ++*str;
        hex_to_utf8(*str, &c);
        *str += 3;
        break;
    default:
        fprintf(stderr, "Invalid escape sequence\n");
        return 0; // Invalid escape sequence
    }
    ++*str;
    return c;
}

int is_control_character(char c)
{
    return c == '\n' || c == '\r' || c == '\t' || c == '\b' || c == '\f';
}

char *json_string_parse(char **str)
{
    char *text = NULL;
    int i = 0;
    int size = 8; // initial size

    if (**str != '"')
        return NULL;
    text = malloc(size + 1);
    if (text == NULL)
        return NULL;
    ++*str;
    while (**str != '"' && **str != '\0')
    {
        if (is_control_character(**str))
        {
            fprintf(stderr, "Control character in string\n");
            free(text);
            return NULL;
        }
        if (i > size)
        {
            size *= 2;
            text = realloc_free_on_fail(text, size + 1);
            if (text == NULL)
            {
                perror("json_string_parse");
                return NULL;
            }
        }
        if (**str == '\\')
        {
            ++*str;
            text[i++] = json_control_character_parse(str);
        }
        else
            text[i++] = **str;
        ++*str;
    }
    if (**str != '"')
    {
        fprintf(stderr, "Unterminated string\n");
        free(text);
        return NULL;
    }
    if (i < size)
    {
        size = i;
        text = realloc_free_on_fail(text, size + 1);
        if (text == NULL)
        {
            perror("json_string_parse");
            return NULL;
        }
    }
    ++*str;
    text[i] = '\0';
    return text;
}
