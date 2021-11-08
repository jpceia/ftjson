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
    char *str = malloc(5);
    
    if (str == NULL)
        return NULL;
    if (boolean)
        strcpy(str, "true");
    else
        strcpy(str, "false");
    return str;
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
    char *str = malloc(4);
    
    if (str == NULL)
        return NULL;
    strcpy(str, "null");
    return str;
}
