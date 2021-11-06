
#include "ftjson.h"
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
