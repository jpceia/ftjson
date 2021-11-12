#include "ftjson.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ---------------------------------------------------------------------------
// NUMBER
// ---------------------------------------------------------------------------

t_json json_from_number(double number)
{
    t_json json;
    
    json.type = JSON_NUMBER;
    json.number = number;
    return json;
}

char *json_number_stringify(double number)
{
    char *str = malloc(32);
    
    if (str == NULL)
        return NULL;
    sprintf(str, "%g", number);
    return str;
}

double json_number_parse(char **str)
{
    double number;
    char *endptr;
    
    number = strtod(*str, &endptr);
    if (endptr == *str)
    {
        *str = NULL;
        return 0;
    }
    *str = endptr;
    return number;
}

// ---------------------------------------------------------------------------
// BOOLEAN
// ---------------------------------------------------------------------------

t_json json_from_boolean(int boolean)
{
    t_json json;
    
    json.type = JSON_BOOLEAN;
    json.boolean = boolean;
    return json;
}

char *json_boolean_stringify(int boolean)
{
    return strdup(boolean ? "true" : "false");
}

// Parses a JSON boolean from a string.
int json_boolean_parse(char **str)
{
    if (!strncmp(*str, "true", 4))
    {
        *str += 4;
        return 1;
    }
    else if (!strncmp(*str, "false", 5))
    {
        *str += 5;
        return 0;
    }
    *str = NULL;
    return -1;
}

// ---------------------------------------------------------------------------
// NULL
// ---------------------------------------------------------------------------

t_json json_from_null(void)
{
    t_json json;
    
    json.type = JSON_NULL;
    return json;
}

char *json_null_stringify(void)
{
    return strdup("null");
}

void json_null_parse(char **str)
{
    char *null_str = "null";

    if (strncmp(*str, null_str, 4) != 0)
    {
        perror("Invalid name");
        *str = NULL;
    }
    *str += 4;
}
